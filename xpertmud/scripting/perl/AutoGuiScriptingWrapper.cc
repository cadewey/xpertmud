#include "AutoGuiScriptingWrapper.h"
#include "../GuiScriptingBindings.h"
#include <qcstring.h>

void GuiScriptingWrapper::XM_Window_close(int id) {
  callBack->XM_Window_close(id);
}

int GuiScriptingWrapper::XM_Window_getPositionX(int id) {
  int ret =
    callBack->XM_Window_getPositionX(id);
  return ret;
}

int GuiScriptingWrapper::XM_Window_getPositionY(int id) {
  int ret =
    callBack->XM_Window_getPositionY(id);
  return ret;
}

int GuiScriptingWrapper::XM_Window_getSizeX(int id) {
  int ret =
    callBack->XM_Window_getSizeX(id);
  return ret;
}

int GuiScriptingWrapper::XM_Window_getSizeY(int id) {
  int ret =
    callBack->XM_Window_getSizeY(id);
  return ret;
}

void GuiScriptingWrapper::XM_Window_hide(int id) {
  callBack->XM_Window_hide(id);
}

void GuiScriptingWrapper::XM_Window_hideCaption(int id) {
  callBack->XM_Window_hideCaption(id);
}

bool GuiScriptingWrapper::XM_Window_isValid(int id) {
  bool ret =
    callBack->XM_Window_isValid(id);
  return ret;
}

void GuiScriptingWrapper::XM_Window_lower(int id) {
  callBack->XM_Window_lower(id);
}

void GuiScriptingWrapper::XM_Window_maximize(int id) {
  callBack->XM_Window_maximize(id);
}

void GuiScriptingWrapper::XM_Window_minimize(int id) {
  callBack->XM_Window_minimize(id);
}

void GuiScriptingWrapper::XM_Window_move(int id,int x,int y) {
  callBack->XM_Window_move(id,x,y);
}

void GuiScriptingWrapper::XM_Window_raise(int id) {
  callBack->XM_Window_raise(id);
}

void GuiScriptingWrapper::XM_Window_resize(int id,int x,int y) {
  callBack->XM_Window_resize(id,x,y);
}

void GuiScriptingWrapper::XM_Window_setTitle(int id,const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  callBack->XM_Window_setTitle(id,qstring);
}

void GuiScriptingWrapper::XM_Window_show(int id) {
  callBack->XM_Window_show(id);
}

void GuiScriptingWrapper::XM_Window_showCaption(int id) {
  callBack->XM_Window_showCaption(id);
}

int GuiScriptingWrapper::XM_TextWindow_initialize() {
  int ret =
    callBack->XM_TextWindow_initialize();
  return ret;
}

void GuiScriptingWrapper::XM_TextWindow_clear(int id) {
  callBack->XM_TextWindow_clear(id);
}

void GuiScriptingWrapper::XM_TextWindow_clearEOL(int id) {
  callBack->XM_TextWindow_clearEOL(id);
}

void GuiScriptingWrapper::XM_TextWindow_clearBOL(int id) {
  callBack->XM_TextWindow_clearBOL(id);
}

void GuiScriptingWrapper::XM_TextWindow_clearEOS(int id) {
  callBack->XM_TextWindow_clearEOS(id);
}

void GuiScriptingWrapper::XM_TextWindow_clearBOS(int id) {
  callBack->XM_TextWindow_clearBOS(id);
}

void GuiScriptingWrapper::XM_TextWindow_clearLine(int id) {
  callBack->XM_TextWindow_clearLine(id);
}

void GuiScriptingWrapper::XM_TextWindow_disableMouseEvents(int id) {
  callBack->XM_TextWindow_disableMouseEvents(id);
}

void GuiScriptingWrapper::XM_TextWindow_enableMouseEvents(int id) {
  callBack->XM_TextWindow_enableMouseEvents(id);
}

char GuiScriptingWrapper::XM_TextWindow_getCharAt(int id,unsigned int x,unsigned int y) {
  char ret =
    callBack->XM_TextWindow_getCharAt(id,x,y);
  return ret;
}

int GuiScriptingWrapper::XM_TextWindow_getColumns(int id) {
  int ret =
    callBack->XM_TextWindow_getColumns(id);
  return ret;
}

int GuiScriptingWrapper::XM_TextWindow_getCursorX(int id) {
  int ret =
    callBack->XM_TextWindow_getCursorX(id);
  return ret;
}

int GuiScriptingWrapper::XM_TextWindow_getCursorY(int id) {
  int ret =
    callBack->XM_TextWindow_getCursorY(id);
  return ret;
}

int GuiScriptingWrapper::XM_TextWindow_getFGColorAt(int id,unsigned int x,unsigned int y) {
  int ret =
    callBack->XM_TextWindow_getFGColorAt(id,x,y);
  return ret;
}

int GuiScriptingWrapper::XM_TextWindow_getBGColorAt(int id,unsigned int x,unsigned int y) {
  int ret =
    callBack->XM_TextWindow_getBGColorAt(id,x,y);
  return ret;
}

int GuiScriptingWrapper::XM_TextWindow_getLines(int id) {
  int ret =
    callBack->XM_TextWindow_getLines(id);
  return ret;
}

void GuiScriptingWrapper::XM_TextWindow_newline(int id) {
  callBack->XM_TextWindow_newline(id);
}

void GuiScriptingWrapper::XM_TextWindow_printRaw(int id,const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  callBack->XM_TextWindow_printRaw(id,qstring);
}

void GuiScriptingWrapper::XM_TextWindow_print(int id,const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  callBack->XM_TextWindow_print(id,qstring);
}

void GuiScriptingWrapper::XM_TextWindow_resetAttributes(int id) {
  callBack->XM_TextWindow_resetAttributes(id);
}

void GuiScriptingWrapper::XM_TextWindow_resizeChars(int id,int x,int y) {
  callBack->XM_TextWindow_resizeChars(id,x,y);
}

void GuiScriptingWrapper::XM_TextWindow_scrollColumns(int id,int cols) {
  callBack->XM_TextWindow_scrollColumns(id,cols);
}

void GuiScriptingWrapper::XM_TextWindow_scrollLines(int id,int lines) {
  callBack->XM_TextWindow_scrollLines(id,lines);
}

void GuiScriptingWrapper::XM_TextWindow_setBold(int id,bool bold) {
  callBack->XM_TextWindow_setBold(id,bold);
}

void GuiScriptingWrapper::XM_TextWindow_setBlinking(int id,bool bold) {
  callBack->XM_TextWindow_setBlinking(id,bold);
}

void GuiScriptingWrapper::XM_TextWindow_setCursor(int id,unsigned int x,unsigned int y) {
  callBack->XM_TextWindow_setCursor(id,x,y);
}

void GuiScriptingWrapper::XM_TextWindow_setDefaultBGColor(int id,int color) {
  callBack->XM_TextWindow_setDefaultBGColor(id,color);
}

void GuiScriptingWrapper::XM_TextWindow_setDefaultFGColor(int id,int color) {
  callBack->XM_TextWindow_setDefaultFGColor(id,color);
}

bool GuiScriptingWrapper::XM_TextWindow_setFont(int id,const char* string,int stringLen,int size) {
  QString qstring = QString::fromUtf8(string, stringLen);
  bool ret =
    callBack->XM_TextWindow_setFont(id,qstring,size);
  return ret;
}

void GuiScriptingWrapper::XM_TextWindow_setIntensive(int id,bool bold) {
  callBack->XM_TextWindow_setIntensive(id,bold);
}

void GuiScriptingWrapper::XM_TextWindow_setReverse(int id,bool bold) {
  callBack->XM_TextWindow_setReverse(id,bold);
}

void GuiScriptingWrapper::XM_TextWindow_setUnderline(int id,bool bold) {
  callBack->XM_TextWindow_setUnderline(id,bold);
}

void GuiScriptingWrapper::XM_TextWindow_setBGColor(int id,int color) {
  callBack->XM_TextWindow_setBGColor(id,color);
}

void GuiScriptingWrapper::XM_TextWindow_setFGColor(int id,int color) {
  callBack->XM_TextWindow_setFGColor(id,color);
}

int GuiScriptingWrapper::XM_TextBufferWindow_initialize() {
  int ret =
    callBack->XM_TextBufferWindow_initialize();
  return ret;
}

int GuiScriptingWrapper::XM_TextBufferWindow_getWordWrapColumn(int id) {
  int ret =
    callBack->XM_TextBufferWindow_getWordWrapColumn(id);
  return ret;
}

void GuiScriptingWrapper::XM_TextBufferWindow_setWordWrapColumn(int id,int col) {
  callBack->XM_TextBufferWindow_setWordWrapColumn(id,col);
}

int GuiScriptingWrapper::XM_Plugin_initialize(const char* libname,int libnameLen,const char* classname,int classnameLen) {
  QString qlibname = QString::fromUtf8(libname, libnameLen);
  QString qclassname = QString::fromUtf8(classname, classnameLen);
  int ret =
    callBack->XM_Plugin_initialize(qlibname,qclassname);
  return ret;
}

LenChar GuiScriptingWrapper::XM_Plugin_call(int id,int fnum,const char* param,int paramLen) {
  QString qparam = QString::fromUtf8(param, paramLen);
  QString ret =
    callBack->XM_Plugin_call(id,fnum,qparam);
  QCString locallyEncoded=ret.utf8();
  LenChar retc; retc.pointer = qstrdup(locallyEncoded.data());
  retc.length = locallyEncoded.length();
  return retc;
}

int GuiScriptingWrapper::XM_Connection_initialize(const char* host,int hostLen,int port,const char* onConnect,int onConnectLen) {
  QString qhost = QString::fromUtf8(host, hostLen);
  QString qonConnect = QString::fromUtf8(onConnect, onConnectLen);
  int ret =
    callBack->XM_Connection_initialize(qhost,port,qonConnect);
  return ret;
}

void GuiScriptingWrapper::XM_Connection_open(int id,const char* host,int hostLen,int port,const char* onConnect,int onConnectLen) {
  QString qhost = QString::fromUtf8(host, hostLen);
  QString qonConnect = QString::fromUtf8(onConnect, onConnectLen);
  callBack->XM_Connection_open(id,qhost,port,qonConnect);
}

void GuiScriptingWrapper::XM_Connection_send(int id,const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  callBack->XM_Connection_send(id,qstring);
}

void GuiScriptingWrapper::XM_Connection_close(int id) {
  callBack->XM_Connection_close(id);
}

void GuiScriptingWrapper::XM_Connection_setInputEncoding(int id,const char* enc,int encLen) {
  QString qenc = QString::fromUtf8(enc, encLen);
  callBack->XM_Connection_setInputEncoding(id,qenc);
}

void GuiScriptingWrapper::XM_Connection_setOutputEncoding(int id,const char* enc,int encLen) {
  QString qenc = QString::fromUtf8(enc, encLen);
  callBack->XM_Connection_setOutputEncoding(id,qenc);
}

int GuiScriptingWrapper::XM_InputLine_getCursorX(int id) {
  int ret =
    callBack->XM_InputLine_getCursorX(id);
  return ret;
}

int GuiScriptingWrapper::XM_InputLine_getCursorY(int id) {
  int ret =
    callBack->XM_InputLine_getCursorY(id);
  return ret;
}

void GuiScriptingWrapper::XM_InputLine_setCursorX(int id,int x) {
  callBack->XM_InputLine_setCursorX(id,x);
}

void GuiScriptingWrapper::XM_InputLine_setCursorY(int id,int y) {
  callBack->XM_InputLine_setCursorY(id,y);
}

LenChar GuiScriptingWrapper::XM_InputLine_getText(int id) {
  QString ret =
    callBack->XM_InputLine_getText(id);
  QCString locallyEncoded=ret.utf8();
  LenChar retc; retc.pointer = qstrdup(locallyEncoded.data());
  retc.length = locallyEncoded.length();
  return retc;
}

void GuiScriptingWrapper::XM_InputLine_setText(int id,const char* text,int textLen) {
  QString qtext = QString::fromUtf8(text, textLen);
  callBack->XM_InputLine_setText(id,qtext);
}

LenChar GuiScriptingWrapper::XM_ansiToColored(const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  QString ret =
    callBack->XM_ansiToColored(qstring);
  QCString locallyEncoded=ret.utf8();
  LenChar retc; retc.pointer = qstrdup(locallyEncoded.data());
  retc.length = locallyEncoded.length();
  return retc;
}

LenChar GuiScriptingWrapper::XM_ansiToRaw(const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  QString ret =
    callBack->XM_ansiToRaw(qstring);
  QCString locallyEncoded=ret.utf8();
  LenChar retc; retc.pointer = qstrdup(locallyEncoded.data());
  retc.length = locallyEncoded.length();
  return retc;
}

void GuiScriptingWrapper::XM_echoMode(bool state) {
  callBack->XM_echoMode(state);
}

int GuiScriptingWrapper::XM_getActiveWindow() {
  int ret =
    callBack->XM_getActiveWindow();
  return ret;
}

int GuiScriptingWrapper::XM_getFocusedInputLine() {
  int ret =
    callBack->XM_getFocusedInputLine();
  return ret;
}

int GuiScriptingWrapper::XM_mdiWidth() {
  int ret =
    callBack->XM_mdiWidth();
  return ret;
}

int GuiScriptingWrapper::XM_mdiHeight() {
  int ret =
    callBack->XM_mdiHeight();
  return ret;
}

void GuiScriptingWrapper::XM_playAudio(const char* filename,int filenameLen) {
  QString qfilename = QString::fromUtf8(filename, filenameLen);
  callBack->XM_playAudio(qfilename);
}

void GuiScriptingWrapper::XM_resetStatusMsg() {
  callBack->XM_resetStatusMsg();
}

void GuiScriptingWrapper::XM_send(const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  callBack->XM_send(qstring);
}

void GuiScriptingWrapper::XM_setStatusMsg(const char* message,int messageLen) {
  QString qmessage = QString::fromUtf8(message, messageLen);
  callBack->XM_setStatusMsg(qmessage);
}

void GuiScriptingWrapper::XM_showError(const char* string,int stringLen) {
  QString qstring = QString::fromUtf8(string, stringLen);
  callBack->XM_showError(qstring);
}

