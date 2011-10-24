#include "TelnetFilter.h"

#ifdef WIN32
#pragma warning( disable : 4514 )
#pragma warning( disable : 4310 )
#endif

#define TELOPTS
#include <arpa/telnet.h>

#ifndef TELOPT_COMPRESS
# define TELOPT_COMPRESS 85
#endif
#ifndef TELOPT_COMPRESS2
# define TELOPT_COMPRESS2 86
#endif

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

TelnetIacAnswer StandardCallback::iacWont(int iac) {
  if(debug) {
    if(iac < NTELOPTS && iac >= 0)
      cout << "Unknown IAC Command: WONT " << telopts[iac];
    else
      cout << "Unknown IAC Command: WONT " << (int)iac;
    cout << ", -> We do not answer anything." << endl;
  }
  return TelnetIacAnswer(false);
}

TelnetIacAnswer StandardCallback::iacDont(int iac) {
  if(debug) {
    if(iac < NTELOPTS && iac >= 0)
      cout << "Unknown IAC Command: DONT " << telopts[iac];
    else
      cout << "Unknown IAC Command: DONT " << (int)iac;
    cout << ", -> We do not answer anything." << endl;
  }
  return TelnetIacAnswer(false);
}

TelnetIacAnswer StandardCallback::iacWill(int iac) {
  if(debug) {
    if(iac < NTELOPTS && iac >= 0)
      cout << "Unknown IAC Command: WILL " << telopts[iac];
    else
      cout << "Unknown IAC Command: WILL " << (int)iac;
    cout << ", -> We answer DONT." << endl;
  }
  return TelnetIacAnswer(true, false);
}

TelnetIacAnswer StandardCallback::iacDo(int iac) {
  if(debug) {
    if(iac < NTELOPTS && iac >= 0)
      cout << "Unknown IAC Command: DO " << telopts[iac];
    else
      cout << "Unknown IAC Command: DO " << (int)iac;
    cout << ", -> We answer WONT." << endl;
  }
  return TelnetIacAnswer(true, false);
}

bool StandardCallback::iacSubNegotiation(int iac, const string& /* unused: command */) {
  if(debug) {
    cout << "Server started subnegotiation for " << telopts[iac] << endl
	 << "without asking :-(" << endl;
  }
  return false;
}

TelnetFilter::TelnetFilter(SenderIface *sender,
			   InputStreamFilter *first,
			   InputStreamFilter *next):
  InputStreamFilter(first, next), 
  sender(sender),
  state(SNORMAL),
  standardCallback(true),
  replaceGA("<IAC><GA>")
{}

TelnetFilter::~TelnetFilter() {}

void TelnetFilter::parse(const string& str) {
  // TODO: Telnet Type Request parsing
  //  cout << "Parsing: " << str << endl;

  string::const_iterator from = str.begin();
  string::const_iterator to;

  for(to=str.begin(); to != str.end(); ++to) {
    // leave this in for debuggin'
    //    if((unsigned char)*to < 32 || (unsigned char)*to > 127) {
    //cout << (int)state << ": "
    //	 << "(" << (int)((unsigned char)*to) << ")" 
    //	 << *to << endl;
    //    }
    switch(state) {
    case SNORMAL:
      if(*to == (char)IAC)
        { sendUntil(from, to); from = to; state = SIAC_START; }
      break;
    case SIAC_START:
      if(*to == (char)DONT) { state = SDONT_START; }
      else if(*to == (char)DO) { state = SDO_START; }
      else if(*to == (char)WONT) { state = SWONT_START; }
      else if(*to == (char)WILL) { state = SWILL_START; }
      else if(*to == (char)SB) { subCommand = ""; state = SSB_START; }
      else if(*to == (char)GA) { 
	cout << "Replacing GA with " << replaceGA << endl;
	sendUntil(replaceGA.begin(), replaceGA.end());
	from = to+1; state = SNORMAL; 
      }
      else if(*to == (char)IAC) { 
	sendUntil(from, to); 
	from = to+1; state=SNORMAL; 
      }
      else if(*to == (char)NOP) { from = to+1; state = SNORMAL; }
      else { state = SNORMAL; }
      break;
    case SDONT_START:
    case SDO_START:
    case SWONT_START:
    case SWILL_START:
      if(executeIacCallback(state, *to)) {
        first->parse(string(to+1, str.end()));
        return; // everything's parsed now
      }
      from = to+1;
      state = SNORMAL;
      break;
    case SSB_START:
      if(*to == (char)IAC) { state = SSB_IAC; }
      else if(*to == (char)SE && subCommand.size() == 2 &&
	      subCommand[0] == (char)TELOPT_COMPRESS &&  //***
	      subCommand[1] == (char)WILL) {          //*** (puking)
	// support for the broken MCCP v1 protocol :-O
	state = SNORMAL;
	if(sendSubCommand()) {
	  first->parse(string(to+1, str.end()));
	  return; // everything's parsed now
	}
	from = to+1; 
      } else { subCommand += *to; }
      break;
    case SSB_IAC:
      if(*to == (char)SE) { 
	state = SNORMAL;
	if(sendSubCommand()) {
	  first->parse(string(to+1, str.end()));
	  return; // everything's parsed now
	}
	from = to+1; 
      } else { subCommand += (char)IAC; subCommand += *to; state = SSB_START; }
      break;
    }
  }
  if(state == SNORMAL) {
    sendUntil(from, to);
  } else {
    cout << "State: " << state << endl;
  }
}

void TelnetFilter::registerIac(int iac, TelnetIacCallback* call) {
  iacMap.insert(mapPairType(iac, call));
}

void TelnetFilter::sendUntil(const string::const_iterator from,
			     const string::const_iterator to) {
  if(next != NULL && from != to) {
    next->parse(string(from, to));
  }
}

bool TelnetFilter::sendSubCommand() {
  int iac = subCommand[0];
  mapType::iterator it = iacMap.lower_bound(iac);
  mapType::iterator end = iacMap.upper_bound(iac);
  
  bool streamChange = false;
  string command(subCommand.begin()+1, subCommand.end());
  while(it != end) {
    streamChange |= it->second->iacSubNegotiation(iac, command);
    ++it;
  }
  return streamChange;
}

bool TelnetFilter::executeIacCallback(EState state, unsigned char command) {
  mapType::iterator it = iacMap.lower_bound(command);
  mapType::iterator end = iacMap.upper_bound(command);

  // debug purposes: dynamic registration... on demand
  if(it == end) {
    cout << "Registering Standard IAC Handler for " << (int)command << endl;
    registerIac(command, &standardCallback);
    it = iacMap.lower_bound(command);
    end = iacMap.upper_bound(command);
    if(it == end) {
      cerr << "Coding error TelnetFilter.cc executeIacCallbac(...)!" << endl;
      //exit(1);
    }
  }

  TelnetIacAnswer ret;
  while(it != end) {
    switch(state) {
    case SDONT_START:
      //cout << "Got DONT " << telopts[command] << endl;
      ret |= ((*it).second)->iacDont(command); break;
    case SDO_START:
      //cout << "Got DO " << telopts[command] << endl;
      ret |= ((*it).second)->iacDo(command); break;
    case SWONT_START:
      //cout << "Got WONT " << telopts[command] << endl;
      ret |= ((*it).second)->iacWont(command); break;
    case SWILL_START:
      /*      cout << (int)&standardCallback  << endl;
      cout << (int)((*it).second) << endl;
      standardCallback.iacWill(0);
      cout << "here" << endl;
      ret |= ((TelnetIacCallback *)&standardCallback)->iacWill((int)command);
      cout << "there" << endl;*/
      //cout << "Got WILL " << telopts[command] << endl;
      ret |= ((*it).second)->iacWill(command); break;
    default:
      cerr << "Wrong state for executeIacCallback!" << endl;
    }
    ++it;
  }
  if(ret.doAnswer) {
    unsigned char retCommand = DONT; // Hopefully sensible default
    if(ret.answer) {
      if(state == SDONT_START || state == SDO_START) { 
        retCommand = WILL; 
      } else if(state == SWONT_START || state == SWILL_START) {
        retCommand = DO;
      }
    } else {
      if(state == SDONT_START || state == SDO_START) { 
        retCommand = WONT; 
      } else if(state == SWONT_START || state == SWILL_START) {
        retCommand = DONT;
      }
    }
    char cmd[] = { retCommand, command };
    sender->sendByte((char)IAC);
    sender->send(cmd, 2);
  }

  return ret.streamTypeChange;
}

