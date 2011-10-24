#include "TextBuffer.h"

#include <ctime>
#include "kapplication.h"
#include <qdir.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <qdatetime.h>
#include <qstring.h>

extern bool logging;
bool lfile = false;
QString xdt = QDateTime::currentDateTime().toString("dd-MM-yyyy-h-m");
std::string fname;
std::ofstream logFile;
//std::string strip_ansi(std::string);

TextBuffer::TextBuffer(int p_id, unsigned int initialWidth, 
		       unsigned int initialHeight,
		       unsigned int ansiViewWidth,
		       unsigned int ansiViewHeight,
		       int wordWrapColumn):
  cursorX(0), cursorY(0),
  ansiViewWidth(ansiViewWidth),
  ansiViewHeight(ansiViewHeight),
  ansiParser(this),
  growBuffer(true), 
  autoFeedForward(true),
  maxBufferSize(0)
{
  parent_id = p_id;
  init(initialWidth, initialHeight, wordWrapColumn);
}

TextBuffer::TextBuffer(int p_id, unsigned int initialWidth, 
		       unsigned int initialHeight,
		       bool growBuffer):
  cursorX(0), cursorY(0),
  ansiParser(this),
  growBuffer(growBuffer),
  autoFeedForward(false),
  maxBufferSize(0)
{
  parent_id = p_id;
  if(!growBuffer) {
    // if we're not growing, we need _some_ size
    // because if !growBuffer then we assume
    // that buffer[0].size() is our fixed width.
    // so buffer[0] _has_ to exist!
    if(initialWidth == 0) initialWidth = 1;
    if(initialHeight == 0) initialHeight = 1;
  }
  ansiViewWidth = initialWidth;
  ansiViewHeight = initialHeight;

  init(initialWidth, initialHeight, 0);
}

TextBuffer::TextBuffer(int p_id, unsigned int initialWidth, 
		       unsigned int initialHeight,
		       int wordWrapColumn,
		       bool growBuffer):
  cursorX(0), cursorY(0),
  ansiParser(this),
  growBuffer(growBuffer), 
  autoFeedForward(true),
  maxBufferSize(0)
{
  parent_id = p_id;
  if(!growBuffer) {
    // if we're not growing, we need _some_ size
    // because if !growBuffer then we assume
    // that buffer[0].size() is our fixed width.
    // so buffer[0] _has_ to exist!
    if(initialWidth == 0) initialWidth = 1;
    if(initialHeight == 0) initialHeight = 1;
  }
  ansiViewWidth = initialWidth;
  ansiViewHeight = initialHeight;

  init(initialWidth, initialHeight, wordWrapColumn);
}

void TextBuffer::init(unsigned int initialWidth,
		      unsigned int initialHeight,
		      int wordWrapColumn) {
  // wordWrapColumn = -ansiViewWidth
  // would be wordWrapColumn = 0, which makes no sense
  if(wordWrapColumn <= (int)ansiViewWidth)
    this->wordWrapColumn = wordWrapColumn;
  else
    this->wordWrapColumn = 0;

  // if !growBuffer than this can't be changed except
  // by resize(), which maintains the aspect ratio;
  // so, if !growBuffer then buffer[0].size() == columns
  // else, every line can have a different size
  buffer.resize(initialHeight);
  for(unsigned int i=0; i<buffer.size(); ++i)
    buffer[i].resize(initialWidth, defaultAttributes);
}

void TextBuffer::printRaw(const QString& text) {
  //  QTime timer;
  //  timer.start();
  //    std::cout << "<Elapsed " << timer.elapsed() << std::endl;

  if(text.length() == 0) return;
// Debugging stuff
/*  int xx = 1;
  std::string stlstring = text.ascii();
  std::cout << "[" << xx << "]printRaw: " << stlstring;
  xx++;*/

  // the rectangle we've been messing with...
  // we're putting them to values they can't ever have;
  // it gets initialized when a char is actually changed
  int minX = -1;
  int maxX = -1;
  int minY = -1;
  int maxY = -1;

  // for every character in our nice text
  for(unsigned int i=0; i<text.length(); ++i) {
	if(text.at(i) != '\n')
    	insertOneChar(text.at(i), minX, maxX, minY, maxY);
  }

  logToFile(text);

  //  qDebug(QString("Emitting (%1, %2) [%3, %4]")
  // .arg(minX).arg(minY).arg(maxX+1-minX).arg(maxY+1-minY));

  //    std::cout << "-Elapsed " << timer.elapsed() << std::endl;

  emit textChanged(minX, minY, maxX+1-minX, maxY+1-minY);

  //    std::cout << ">Elapsed " << timer.elapsed() << std::endl;
}

void TextBuffer::print(const QString& text) {

  // whould be like
  ansiParser.parse(text);

  // once the ansi parser can handle QString
  // print(std::string(text.latin1()));
}

void TextBuffer::logToFile(const QString& text) {
    // FIXME
    std::string stripped_text = text.ascii() ;
    // Make sure this is text going to the main status window
    //std::cout << "Char's parent: " << parent_id << std::endl;
    if ( ( logging ) && ( parent_id == 0 ) ) {
      if (lfile) {
          logFile << stripped_text;
      } else {
          QDir temp;
          fname = xdt.ascii();
          QString home = QDir::homeDirPath();
          std::string strhome = home.ascii();
          std::string fpath = strhome + "/.xpertmud/";
          home = QString::fromUtf8(fpath.c_str());
          if ( !temp.exists(home) ) {
              std::cout << "Creating ~/.xpertmud/" << std::endl;
              temp.mkdir(home, TRUE);
          }
          temp.~QDir();
          fpath = fpath + fname + ".log";
          std::cout << "Logging path: " << fpath.c_str() << std::endl;
          logFile.open(fpath.c_str());
          lfile = true;
          logFile << stripped_text;
      }
    } else if ( ( !logging ) && ( lfile ) ) {
        logFile.close();
        lfile = false;
    }
}

void TextBuffer::clearEOL() {
  unsigned int line = getLine(cursorY);

  if(line < buffer.size()) {
    unsigned int columns = buffer[line].size();

    if(cursorX < columns) {
      buffer[line].resize(cursorX);

      if(!growBuffer)
	buffer[line].resize(columns, defaultAttributes);

      emit textChanged(cursorX, line, columns-cursorX, 1);
    }
  }
}

void TextBuffer::clearBOL() {
  unsigned int line = getLine(cursorY);

  if(line < buffer.size()) {
    unsigned int width = QMIN(cursorX, buffer[line].size());
    for(unsigned int i=0; i<width; ++i)
      buffer[line][i] = defaultAttributes;

    emit textChanged(0, line, width, 1);
  }
}

void TextBuffer::clearLine() {
  unsigned int line = getLine(cursorY);

  if(line < buffer.size()) {
    unsigned int columns = buffer[line].size();
    buffer[line].clear();
    if(!growBuffer)
      buffer[line].resize(columns, defaultAttributes);

    emit textChanged(0, line, columns, 1);
  }
}

void TextBuffer::clearEOS() {
  unsigned int saveY = cursorY;

  clearEOL();
  ++cursorY;
  while(cursorY < ansiViewHeight) {
    clearLine();
    ++cursorY;
  }

  cursorY = saveY;
  emit textChanged();
}

void TextBuffer::clearBOS() {
  unsigned int saveY= cursorY;

  clearBOL();
  if(cursorY > 0) { // ATTENTION: unsigned int
    do {
      --cursorY;
      clearLine();
    } while(cursorY > 0);
  }

  cursorY = saveY;
  emit textChanged();
}

void TextBuffer::clearWindow() {
  setCursor(0, 0);
  for(int i=buffer.size()-ansiViewHeight; 0<=i && i<(int)buffer.size(); ++i) {
    unsigned int columns = buffer[i].size();
    buffer[i].clear();
    if(!growBuffer)
      buffer[i].resize(columns, defaultAttributes);
  }

  emit textChanged();
}

void TextBuffer::newline() {
  cursorX = 0;
  if(cursorY < ansiViewHeight-1)
    ++cursorY;
  else {
    if(growBuffer) {
      unsigned int line = buffer.size();
      createPosition(0, line);
    } else {
      scrollLines(1);
    }
  }
}

void TextBuffer::tab() {
  do {
    printRaw(QString(" "));
  } while(cursorX % 8 != 0);
}

void TextBuffer::backspace() {
  if(cursorX > 0)
    --cursorX;
}

void TextBuffer::beep() {
  KApplication::beep();
}

void TextBuffer::carriageReturn() {
  cursorX = 0;
}

void TextBuffer::scrollLines(int delta) {
  if(delta == 0) return;
  if((unsigned int)QABS(delta) >= ansiViewHeight)
    clearWindow();

  if(delta > 0) {
    for(int i=buffer.size()-ansiViewHeight; 0<=i && i<(int)buffer.size(); ++i) {
      if(i < (int)buffer.size() - delta) {
	buffer[i].swap(buffer[i+delta]);
      } else {
	unsigned int columns = buffer[i].size();
	buffer[i].clear();
	if(!growBuffer)
	  buffer[i].resize(columns, defaultAttributes);
      }
    }
  } else {
    for(int i=buffer.size()-1; i>=0; --i) {
      if(i >= -delta) {
	buffer[i].swap(buffer[i+delta]);
      } else {
	unsigned int columns = buffer[i].size();
	buffer[i].clear();
	if(!growBuffer) {
	  buffer[i].resize(columns, defaultAttributes);
	}
      }
    }
  }
  emit scrolledLines(delta);
}

void TextBuffer::scrollColumns(int delta) {
  if(delta == 0) return;
  if((unsigned int)QABS(delta) >= ansiViewWidth)
    clearWindow();
  
  if(delta > 0) {
    for(int y=buffer.size()-ansiViewHeight; 0<=y && y<(int)buffer.size(); ++y) {
      for(unsigned int x=0; x<buffer[y].size(); ++x) {
	if(x < ansiViewWidth-delta && x+delta < buffer[y].size()) {
	  buffer[y][x] = buffer[y][x+delta];
	}
      }
      unsigned int columns = buffer[y].size();
      buffer[y].resize(ansiViewWidth - delta);
      if(!growBuffer)
	buffer[y].resize(columns, defaultAttributes);
    }
  } else {
    for(int y=buffer.size()-ansiViewHeight; 0<=y && y<(int)buffer.size(); ++y) {
      if(buffer[y].size() < ansiViewWidth) {
	buffer[y].resize(QMIN(buffer[y].size()-delta,
				  ansiViewWidth));
      }
      for(int x=buffer[y].size()-1; x>=0; --x) {
	if(x >= -delta)
	  buffer[y][x] = buffer[y][x+delta];
	else
	  buffer[y][x] = defaultAttributes;
      }
    }
  }
  emit scrolledColumns(delta);
}

void TextBuffer::setDefaultFGColor(int color) {
  defaultAttributes.setFg(color); 
}

void TextBuffer::setDefaultBGColor(int color) {
  defaultAttributes.setBg(color); 
}

void TextBuffer::resize(unsigned int width, unsigned int height) {
  // cursorX is relative to left
  cursorX = QMIN(cursorX, width - 1);

  // cursorY is relative to bottom
  int toBottom = ansiViewHeight - cursorY;
  int newY = QMIN(QMAX(0, (int)height - toBottom),
		     (int)height - 1);

  // don't go into unfilled area...
  if(newY >= (int)buffer.size()) {
    newY = QMAX((int)buffer.size()-1, 0);
  }
  cursorY = newY;

  ansiViewWidth = width;
  ansiViewHeight = height;
  if(!growBuffer) {
    buffer.resize(ansiViewHeight);
    for(unsigned int line=0; line<buffer.size(); ++line) {
      buffer[line].resize(ansiViewWidth, defaultAttributes);
    }
  }
}

