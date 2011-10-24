#ifndef GUISCRIPTINGWRAPPER_H
#define GUISCRIPTINGWRAPPER_H

class GuiScriptingBindings;

struct LenChar {
  char* pointer;
  int   length;
};

class GuiScriptingWrapper {
public:
  GuiScriptingWrapper(): callBack(0) {}
  void setCallback(GuiScriptingBindings* callBack) {
    this->callBack = callBack;
  }

#undef bool
  void XM_Window_close(int id);
  int XM_Window_getPositionX(int id);
  int XM_Window_getPositionY(int id);
  int XM_Window_getSizeX(int id);
  int XM_Window_getSizeY(int id);
  void XM_Window_hide(int id);
  void XM_Window_hideCaption(int id);
  bool XM_Window_isValid(int id);
  void XM_Window_lower(int id);
  void XM_Window_maximize(int id);
  void XM_Window_minimize(int id);
  void XM_Window_move(int id,int x,int y);
  void XM_Window_raise(int id);
  void XM_Window_resize(int id,int x,int y);
  void XM_Window_setTitle(int id,const char* string,int stringLen);
  void XM_Window_show(int id);
  void XM_Window_showCaption(int id);
  int XM_TextWindow_initialize();
  void XM_TextWindow_clear(int id);
  void XM_TextWindow_clearEOL(int id);
  void XM_TextWindow_clearBOL(int id);
  void XM_TextWindow_clearEOS(int id);
  void XM_TextWindow_clearBOS(int id);
  void XM_TextWindow_clearLine(int id);
  void XM_TextWindow_disableMouseEvents(int id);
  void XM_TextWindow_enableMouseEvents(int id);
  char XM_TextWindow_getCharAt(int id,unsigned int x,unsigned int y);
  int XM_TextWindow_getColumns(int id);
  int XM_TextWindow_getCursorX(int id);
  int XM_TextWindow_getCursorY(int id);
  int XM_TextWindow_getFGColorAt(int id,unsigned int x,unsigned int y);
  int XM_TextWindow_getBGColorAt(int id,unsigned int x,unsigned int y);
  int XM_TextWindow_getLines(int id);
  void XM_TextWindow_newline(int id);
  void XM_TextWindow_printRaw(int id,const char* string,int stringLen);
  void XM_TextWindow_print(int id,const char* string,int stringLen);
  void XM_TextWindow_resetAttributes(int id);
  void XM_TextWindow_resizeChars(int id,int x,int y);
  void XM_TextWindow_scrollColumns(int id,int cols);
  void XM_TextWindow_scrollLines(int id,int lines);
  void XM_TextWindow_setBold(int id,bool bold);
  void XM_TextWindow_setBlinking(int id,bool bold);
  void XM_TextWindow_setCursor(int id,unsigned int x,unsigned int y);
  void XM_TextWindow_setDefaultBGColor(int id,int color);
  void XM_TextWindow_setDefaultFGColor(int id,int color);
  bool XM_TextWindow_setFont(int id,const char* string,int stringLen,int size);
  void XM_TextWindow_setIntensive(int id,bool bold);
  void XM_TextWindow_setReverse(int id,bool bold);
  void XM_TextWindow_setUnderline(int id,bool bold);
  void XM_TextWindow_setBGColor(int id,int color);
  void XM_TextWindow_setFGColor(int id,int color);
  int XM_TextBufferWindow_initialize();
  int XM_TextBufferWindow_getWordWrapColumn(int id);
  void XM_TextBufferWindow_setWordWrapColumn(int id,int col);
  int XM_Plugin_initialize(const char* libname,int libnameLen,const char* classname,int classnameLen);
  LenChar XM_Plugin_call(int id,int fnum,const char* param,int paramLen);
  int XM_Connection_initialize(const char* host,int hostLen,int port,const char* onConnect,int onConnectLen);
  void XM_Connection_open(int id,const char* host,int hostLen,int port,const char* onConnect,int onConnectLen);
  void XM_Connection_send(int id,const char* string,int stringLen);
  void XM_Connection_close(int id);
  void XM_Connection_setInputEncoding(int id,const char* enc,int encLen);
  void XM_Connection_setOutputEncoding(int id,const char* enc,int encLen);
  int XM_InputLine_getCursorX(int id);
  int XM_InputLine_getCursorY(int id);
  void XM_InputLine_setCursorX(int id,int x);
  void XM_InputLine_setCursorY(int id,int y);
  LenChar XM_InputLine_getText(int id);
  void XM_InputLine_setText(int id,const char* text,int textLen);
  LenChar XM_ansiToColored(const char* string,int stringLen);
  LenChar XM_ansiToRaw(const char* string,int stringLen);
  void XM_echoMode(bool state);
  int XM_getActiveWindow();
  int XM_getFocusedInputLine();
  int XM_mdiWidth();
  int XM_mdiHeight();
  void XM_playAudio(const char* filename,int filenameLen);
  void XM_resetStatusMsg();
  void XM_send(const char* string,int stringLen);
  void XM_setStatusMsg(const char* message,int messageLen);
  void XM_showError(const char* string,int stringLen);

private:
  GuiScriptingBindings* callBack;
};

#endif
