// -*- c++ -*-
#include "PerlInterpret.h"

#include <cstdio>
// using snprintf;

// perl headers
extern "C" {
#  include <EXTERN.h>
#  include <perl.h>
#  include <XSUB.h>
}

#include "AutoGuiScriptingWrapper.h"

#define NO_MULTILINE_STRING 1
#ifndef NO_MULTILINE_STRING
#include "sysinit_pl.h"
#else
#include "sysinit_plf.h"
#endif

#ifdef WIN32
#undef bool
#define snprintf _snprintf
#endif

// Stupid perl version incompatibilities...
#ifdef dXSTARG
#define FIXWARN
#else
#define dXSTARG
#endif

// TODO: add configure test! 5.6.1 compatibility mode as default
#undef FIXWARN

// Get rid of those stupid warnings
#ifdef FIXWARN
#define FIXPERLWARN  if(false) { cv+=0; Perl___notused+=0; }
#define FIXPERLWARN2  if (false) { targ+=0; }
#else
#define FIXPERLWARN
#define FIXPERLWARN2
#endif

// set from PerlInterpret while interpreting perl code
static GuiScriptingWrapper *currentCallBack;

#define LOAD_ID \
    int id = -1; \
    if (SvROK(ST(0)) && SvTYPE(SvRV(ST(0)))==SVt_PVHV) { \
      HV* hash=(HV*)SvRV(ST(0)); \
      SV** sid=hv_fetch(hash,"_ID",3,0); \
      if (sid && SvIOK(*sid)) \
	id=SvIV(*sid); \
      else \
	croak("Invalid Parameter: Hash did not contain a int '_ID' key"); \
    } else \
      croak("Invalid Parameter: Object needs to be blessed Hashref");




extern "C" {
  void boot_DynaLoader (pTHX_ CV* cv);


  XS(XM_Window_close) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::close()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_close(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_getPositionX) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::getPositionX()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_Window_getPositionX(id);
    XSRETURN_IV(ret);
  }

  XS(XM_Window_getPositionY) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::getPositionY()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_Window_getPositionY(id);
    XSRETURN_IV(ret);
  }

  XS(XM_Window_getSizeX) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::getSizeX()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_Window_getSizeX(id);
    XSRETURN_IV(ret);
  }

  XS(XM_Window_getSizeY) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::getSizeY()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_Window_getSizeY(id);
    XSRETURN_IV(ret);
  }

  XS(XM_Window_hide) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::hide()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_hide(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_hideCaption) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::hideCaption()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_hideCaption(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_isValid) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::isValid()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    bool ret = currentCallBack->
        XM_Window_isValid(id);
    if(ret)
      XSRETURN_YES;
    else
      XSRETURN_NO;
  }

  XS(XM_Window_lower) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::lower()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_lower(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_maximize) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::maximize()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_maximize(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_minimize) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::minimize()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_minimize(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_move) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMWindow::move($x, $y)");

    LOAD_ID;

    int x;
    x = SvIV(ST(1));

    int y;
    y = SvIV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_move(id,x,y);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_raise) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::raise()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_raise(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_resize) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMWindow::resize($x, $y)");

    LOAD_ID;

    int x;
    x = SvIV(ST(1));

    int y;
    y = SvIV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_resize(id,x,y);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_setTitle) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMWindow::setTitle($string)");

    LOAD_ID;

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(1), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_setTitle(id,string,stringLen);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_show) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::show()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_show(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Window_showCaption) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMWindow::showCaption()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Window_showCaption(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_initialize) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 0)
      croak("Usage: XMTextWindow::initialize()");

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextWindow_initialize();
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_clear) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::clear()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_clear(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_clearEOL) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::clearEOL()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_clearEOL(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_clearBOL) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::clearBOL()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_clearBOL(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_clearEOS) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::clearEOS()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_clearEOS(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_clearBOS) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::clearBOS()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_clearBOS(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_clearLine) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::clearLine()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_clearLine(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_disableMouseEvents) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::disableMouseEvents()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_disableMouseEvents(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_enableMouseEvents) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::enableMouseEvents()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_enableMouseEvents(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_getCharAt) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMTextWindow::getCharAt($x, $y)");

    LOAD_ID;

    unsigned int x;
    x = SvUV(ST(1));

    unsigned int y;
    y = SvUV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    char ret = currentCallBack->
        XM_TextWindow_getCharAt(id,x,y);
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_getColumns) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::getColumns()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextWindow_getColumns(id);
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_getCursorX) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::getCursorX()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextWindow_getCursorX(id);
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_getCursorY) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::getCursorY()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextWindow_getCursorY(id);
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_getFGColorAt) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMTextWindow::getFGColorAt($x, $y)");

    LOAD_ID;

    unsigned int x;
    x = SvUV(ST(1));

    unsigned int y;
    y = SvUV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextWindow_getFGColorAt(id,x,y);
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_getBGColorAt) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMTextWindow::getBGColorAt($x, $y)");

    LOAD_ID;

    unsigned int x;
    x = SvUV(ST(1));

    unsigned int y;
    y = SvUV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextWindow_getBGColorAt(id,x,y);
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_getLines) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::getLines()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextWindow_getLines(id);
    XSRETURN_IV(ret);
  }

  XS(XM_TextWindow_newline) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::newline()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_newline(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_printRaw) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::printRaw($string)");

    LOAD_ID;

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(1), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_printRaw(id,string,stringLen);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_print) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::print($string)");

    LOAD_ID;

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(1), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_print(id,string,stringLen);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_resetAttributes) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextWindow::resetAttributes()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_resetAttributes(id);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_resizeChars) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMTextWindow::resizeChars($x, $y)");

    LOAD_ID;

    int x;
    x = SvIV(ST(1));

    int y;
    y = SvIV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_resizeChars(id,x,y);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_scrollColumns) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::scrollColumns($cols)");

    LOAD_ID;

    int cols;
    cols = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_scrollColumns(id,cols);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_scrollLines) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::scrollLines($lines)");

    LOAD_ID;

    int lines;
    lines = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_scrollLines(id,lines);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setBold) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setBold($bold)");

    LOAD_ID;

    bool bold;
    bold = (SvIV(ST(1)) != 0);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setBold(id,bold);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setBlinking) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setBlinking($bold)");

    LOAD_ID;

    bool bold;
    bold = (SvIV(ST(1)) != 0);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setBlinking(id,bold);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setCursor) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMTextWindow::setCursor($x, $y)");

    LOAD_ID;

    unsigned int x;
    x = SvUV(ST(1));

    unsigned int y;
    y = SvUV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setCursor(id,x,y);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setDefaultBGColor) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setDefaultBGColor($color)");

    LOAD_ID;

    int color;
    color = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setDefaultBGColor(id,color);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setDefaultFGColor) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setDefaultFGColor($color)");

    LOAD_ID;

    int color;
    color = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setDefaultFGColor(id,color);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setFont) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMTextWindow::setFont($string, $size)");

    LOAD_ID;

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(1), stringLen);

    int size;
    size = SvIV(ST(2));

    dXSTARG;
    FIXPERLWARN2;

    bool ret = currentCallBack->
        XM_TextWindow_setFont(id,string,stringLen,size);
    if(ret)
      XSRETURN_YES;
    else
      XSRETURN_NO;
  }

  XS(XM_TextWindow_setIntensive) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setIntensive($bold)");

    LOAD_ID;

    bool bold;
    bold = (SvIV(ST(1)) != 0);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setIntensive(id,bold);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setReverse) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setReverse($bold)");

    LOAD_ID;

    bool bold;
    bold = (SvIV(ST(1)) != 0);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setReverse(id,bold);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setUnderline) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setUnderline($bold)");

    LOAD_ID;

    bool bold;
    bold = (SvIV(ST(1)) != 0);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setUnderline(id,bold);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setBGColor) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setBGColor($color)");

    LOAD_ID;

    int color;
    color = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setBGColor(id,color);
    XSRETURN_UNDEF;
  }

  XS(XM_TextWindow_setFGColor) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextWindow::setFGColor($color)");

    LOAD_ID;

    int color;
    color = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextWindow_setFGColor(id,color);
    XSRETURN_UNDEF;
  }

  XS(XM_TextBufferWindow_initialize) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 0)
      croak("Usage: XMTextBufferWindow::initialize()");

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextBufferWindow_initialize();
    XSRETURN_IV(ret);
  }

  XS(XM_TextBufferWindow_getWordWrapColumn) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMTextBufferWindow::getWordWrapColumn()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_TextBufferWindow_getWordWrapColumn(id);
    XSRETURN_IV(ret);
  }

  XS(XM_TextBufferWindow_setWordWrapColumn) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMTextBufferWindow::setWordWrapColumn($col)");

    LOAD_ID;

    int col;
    col = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_TextBufferWindow_setWordWrapColumn(id,col);
    XSRETURN_UNDEF;
  }

  XS(XM_Plugin_initialize) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 2)
      croak("Usage: XMPlugin::initialize($libname, $classname)");

    const char* libname;
    STRLEN libnameLen = 0;
    libname = SvPV(ST(0), libnameLen);

    const char* classname;
    STRLEN classnameLen = 0;
    classname = SvPV(ST(1), classnameLen);

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_Plugin_initialize(libname,libnameLen,classname,classnameLen);
    XSRETURN_IV(ret);
  }

  XS(XM_Plugin_call) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMPlugin::call($fnum, $param)");

    LOAD_ID;

    int fnum;
    fnum = SvIV(ST(1));

    const char* param;
    STRLEN paramLen = 0;
    param = SvPV(ST(2), paramLen);

    dXSTARG;
    FIXPERLWARN2;

    LenChar ret = currentCallBack->
        XM_Plugin_call(id,fnum,param,paramLen);
    if(ret.pointer) {
      ST(0)=sv_2mortal(newSVpv(ret.pointer,ret.length));
      SvUTF8_on(ST(0));     delete[] ret.pointer;
      XSRETURN(1);
    } else {
      XSRETURN_UNDEF;
    }
  }

  XS(XM_Connection_initialize) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 3)
      croak("Usage: XMConnection::initialize($host, $port, $onConnect = "")");

    const char* host;
    STRLEN hostLen = 0;
    host = SvPV(ST(0), hostLen);

    int port;
    port = SvIV(ST(1));

    const char* onConnect = "";
    STRLEN onConnectLen = strlen(onConnect);
    if(items > 2)
      onConnect = SvPV(ST(2), onConnectLen);

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_Connection_initialize(host,hostLen,port,onConnect,onConnectLen);
    XSRETURN_IV(ret);
  }

  XS(XM_Connection_open) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 2 || items > 4)
      croak("Usage: XMConnection::open($host, $port, $onConnect = "")");

    LOAD_ID;

    const char* host;
    STRLEN hostLen = 0;
    host = SvPV(ST(1), hostLen);

    int port;
    port = SvIV(ST(2));

    const char* onConnect = "";
    STRLEN onConnectLen = strlen(onConnect);
    if(items > 3)
      onConnect = SvPV(ST(3), onConnectLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Connection_open(id,host,hostLen,port,onConnect,onConnectLen);
    XSRETURN_UNDEF;
  }

  XS(XM_Connection_send) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMConnection::send($string)");

    LOAD_ID;

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(1), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Connection_send(id,string,stringLen);
    XSRETURN_UNDEF;
  }

  XS(XM_Connection_close) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMConnection::close()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Connection_close(id);
    XSRETURN_UNDEF;
  }

  XS(XM_Connection_setInputEncoding) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMConnection::setInputEncoding($enc)");

    LOAD_ID;

    const char* enc;
    STRLEN encLen = 0;
    enc = SvPV(ST(1), encLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Connection_setInputEncoding(id,enc,encLen);
    XSRETURN_UNDEF;
  }

  XS(XM_Connection_setOutputEncoding) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMConnection::setOutputEncoding($enc)");

    LOAD_ID;

    const char* enc;
    STRLEN encLen = 0;
    enc = SvPV(ST(1), encLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_Connection_setOutputEncoding(id,enc,encLen);
    XSRETURN_UNDEF;
  }

  XS(XM_InputLine_getCursorX) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMInputLine::getCursorX()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_InputLine_getCursorX(id);
    XSRETURN_IV(ret);
  }

  XS(XM_InputLine_getCursorY) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMInputLine::getCursorY()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_InputLine_getCursorY(id);
    XSRETURN_IV(ret);
  }

  XS(XM_InputLine_setCursorX) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMInputLine::setCursorX($x)");

    LOAD_ID;

    int x;
    x = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_InputLine_setCursorX(id,x);
    XSRETURN_UNDEF;
  }

  XS(XM_InputLine_setCursorY) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMInputLine::setCursorY($y)");

    LOAD_ID;

    int y;
    y = SvIV(ST(1));

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_InputLine_setCursorY(id,y);
    XSRETURN_UNDEF;
  }

  XS(XM_InputLine_getText) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 0 || items > 1)
      croak("Usage: XMInputLine::getText()");

    LOAD_ID;

    dXSTARG;
    FIXPERLWARN2;

    LenChar ret = currentCallBack->
        XM_InputLine_getText(id);
    if(ret.pointer) {
      ST(0)=sv_2mortal(newSVpv(ret.pointer,ret.length));
      SvUTF8_on(ST(0));     delete[] ret.pointer;
      XSRETURN(1);
    } else {
      XSRETURN_UNDEF;
    }
  }

  XS(XM_InputLine_setText) {
    dXSARGS;
    FIXPERLWARN;

    if(items < 1 || items > 2)
      croak("Usage: XMInputLine::setText($text)");

    LOAD_ID;

    const char* text;
    STRLEN textLen = 0;
    text = SvPV(ST(1), textLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_InputLine_setText(id,text,textLen);
    XSRETURN_UNDEF;
  }

  XS(XM_ansiToColored) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 1)
      croak("Usage: XM::ansiToColored($string)");

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(0), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    LenChar ret = currentCallBack->
        XM_ansiToColored(string,stringLen);
    if(ret.pointer) {
      ST(0)=sv_2mortal(newSVpv(ret.pointer,ret.length));
      SvUTF8_on(ST(0));     delete[] ret.pointer;
      XSRETURN(1);
    } else {
      XSRETURN_UNDEF;
    }
  }

  XS(XM_ansiToRaw) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 1)
      croak("Usage: XM::ansiToRaw($string)");

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(0), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    LenChar ret = currentCallBack->
        XM_ansiToRaw(string,stringLen);
    if(ret.pointer) {
      ST(0)=sv_2mortal(newSVpv(ret.pointer,ret.length));
      SvUTF8_on(ST(0));     delete[] ret.pointer;
      XSRETURN(1);
    } else {
      XSRETURN_UNDEF;
    }
  }

  XS(XM_echoMode) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 1)
      croak("Usage: XM::echoMode($state)");

    bool state;
    state = (SvIV(ST(0)) != 0);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_echoMode(state);
    XSRETURN_UNDEF;
  }

  XS(XM_getActiveWindow) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 0)
      croak("Usage: XM::getActiveWindow()");

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_getActiveWindow();
    XSRETURN_IV(ret);
  }

  XS(XM_getFocusedInputLine) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 0)
      croak("Usage: XM::getFocusedInputLine()");

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_getFocusedInputLine();
    XSRETURN_IV(ret);
  }

  XS(XM_mdiWidth) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 0)
      croak("Usage: XM::mdiWidth()");

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_mdiWidth();
    XSRETURN_IV(ret);
  }

  XS(XM_mdiHeight) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 0)
      croak("Usage: XM::mdiHeight()");

    dXSTARG;
    FIXPERLWARN2;

    int ret = currentCallBack->
        XM_mdiHeight();
    XSRETURN_IV(ret);
  }

  XS(XM_playAudio) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 1)
      croak("Usage: XM::playAudio($filename)");

    const char* filename;
    STRLEN filenameLen = 0;
    filename = SvPV(ST(0), filenameLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_playAudio(filename,filenameLen);
    XSRETURN_UNDEF;
  }

  XS(XM_resetStatusMsg) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 0)
      croak("Usage: XM::resetStatusMsg()");

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_resetStatusMsg();
    XSRETURN_UNDEF;
  }

  XS(XM_send) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 1)
      croak("Usage: XM::send($string)");

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(0), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_send(string,stringLen);
    XSRETURN_UNDEF;
  }

  XS(XM_setStatusMsg) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 1)
      croak("Usage: XM::setStatusMsg($message)");

    const char* message;
    STRLEN messageLen = 0;
    message = SvPV(ST(0), messageLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_setStatusMsg(message,messageLen);
    XSRETURN_UNDEF;
  }

  XS(XM_showError) {
    dXSARGS;
    FIXPERLWARN;

    if(items != 1)
      croak("Usage: XM::showError($string)");

    const char* string;
    STRLEN stringLen = 0;
    string = SvPV(ST(0), stringLen);

    dXSTARG;
    FIXPERLWARN2;

    currentCallBack->
        XM_showError(string,stringLen);
    XSRETURN_UNDEF;
  }

  // Needs Perl >= 5.6.0 (or patched 5.0)
  // not automagically generated callback

  XS(XM_weaken) {
    dXSARGS;
    FIXPERLWARN;
    if (items != 1)
      croak("Usage: XM::weaken(ref)");

    if (SvROK(ST(0)))
      sv_rvweaken(ST(0));
    else
      croak("Usage: XM::weaken(REF)");

    dXSTARG;
    FIXPERLWARN2;
    XSRETURN_YES;
  }

  void xs_init(pTHX) {
    newXS((char *)"DynaLoader::boot_DynaLoader", boot_DynaLoader, (char *)__FILE__); 

   newXS((char*)"XMWindow::close",
        XM_Window_close, (char*)__FILE__);
   newXS((char*)"XMWindow::getPositionX",
        XM_Window_getPositionX, (char*)__FILE__);
   newXS((char*)"XMWindow::getPositionY",
        XM_Window_getPositionY, (char*)__FILE__);
   newXS((char*)"XMWindow::getSizeX",
        XM_Window_getSizeX, (char*)__FILE__);
   newXS((char*)"XMWindow::getSizeY",
        XM_Window_getSizeY, (char*)__FILE__);
   newXS((char*)"XMWindow::hide",
        XM_Window_hide, (char*)__FILE__);
   newXS((char*)"XMWindow::hideCaption",
        XM_Window_hideCaption, (char*)__FILE__);
   newXS((char*)"XMWindow::isValid",
        XM_Window_isValid, (char*)__FILE__);
   newXS((char*)"XMWindow::lower",
        XM_Window_lower, (char*)__FILE__);
   newXS((char*)"XMWindow::maximize",
        XM_Window_maximize, (char*)__FILE__);
   newXS((char*)"XMWindow::minimize",
        XM_Window_minimize, (char*)__FILE__);
   newXS((char*)"XMWindow::move",
        XM_Window_move, (char*)__FILE__);
   newXS((char*)"XMWindow::raise",
        XM_Window_raise, (char*)__FILE__);
   newXS((char*)"XMWindow::resize",
        XM_Window_resize, (char*)__FILE__);
   newXS((char*)"XMWindow::setTitle",
        XM_Window_setTitle, (char*)__FILE__);
   newXS((char*)"XMWindow::show",
        XM_Window_show, (char*)__FILE__);
   newXS((char*)"XMWindow::showCaption",
        XM_Window_showCaption, (char*)__FILE__);
   newXS((char*)"XMTextWindow::initialize",
        XM_TextWindow_initialize, (char*)__FILE__);
   newXS((char*)"XMTextWindow::clear",
        XM_TextWindow_clear, (char*)__FILE__);
   newXS((char*)"XMTextWindow::clearEOL",
        XM_TextWindow_clearEOL, (char*)__FILE__);
   newXS((char*)"XMTextWindow::clearBOL",
        XM_TextWindow_clearBOL, (char*)__FILE__);
   newXS((char*)"XMTextWindow::clearEOS",
        XM_TextWindow_clearEOS, (char*)__FILE__);
   newXS((char*)"XMTextWindow::clearBOS",
        XM_TextWindow_clearBOS, (char*)__FILE__);
   newXS((char*)"XMTextWindow::clearLine",
        XM_TextWindow_clearLine, (char*)__FILE__);
   newXS((char*)"XMTextWindow::disableMouseEvents",
        XM_TextWindow_disableMouseEvents, (char*)__FILE__);
   newXS((char*)"XMTextWindow::enableMouseEvents",
        XM_TextWindow_enableMouseEvents, (char*)__FILE__);
   newXS((char*)"XMTextWindow::getCharAt",
        XM_TextWindow_getCharAt, (char*)__FILE__);
   newXS((char*)"XMTextWindow::getColumns",
        XM_TextWindow_getColumns, (char*)__FILE__);
   newXS((char*)"XMTextWindow::getCursorX",
        XM_TextWindow_getCursorX, (char*)__FILE__);
   newXS((char*)"XMTextWindow::getCursorY",
        XM_TextWindow_getCursorY, (char*)__FILE__);
   newXS((char*)"XMTextWindow::getFGColorAt",
        XM_TextWindow_getFGColorAt, (char*)__FILE__);
   newXS((char*)"XMTextWindow::getBGColorAt",
        XM_TextWindow_getBGColorAt, (char*)__FILE__);
   newXS((char*)"XMTextWindow::getLines",
        XM_TextWindow_getLines, (char*)__FILE__);
   newXS((char*)"XMTextWindow::newline",
        XM_TextWindow_newline, (char*)__FILE__);
   newXS((char*)"XMTextWindow::printRaw",
        XM_TextWindow_printRaw, (char*)__FILE__);
   newXS((char*)"XMTextWindow::print",
        XM_TextWindow_print, (char*)__FILE__);
   newXS((char*)"XMTextWindow::resetAttributes",
        XM_TextWindow_resetAttributes, (char*)__FILE__);
   newXS((char*)"XMTextWindow::resizeChars",
        XM_TextWindow_resizeChars, (char*)__FILE__);
   newXS((char*)"XMTextWindow::scrollColumns",
        XM_TextWindow_scrollColumns, (char*)__FILE__);
   newXS((char*)"XMTextWindow::scrollLines",
        XM_TextWindow_scrollLines, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setBold",
        XM_TextWindow_setBold, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setBlinking",
        XM_TextWindow_setBlinking, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setCursor",
        XM_TextWindow_setCursor, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setDefaultBGColor",
        XM_TextWindow_setDefaultBGColor, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setDefaultFGColor",
        XM_TextWindow_setDefaultFGColor, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setFont",
        XM_TextWindow_setFont, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setIntensive",
        XM_TextWindow_setIntensive, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setReverse",
        XM_TextWindow_setReverse, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setUnderline",
        XM_TextWindow_setUnderline, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setBGColor",
        XM_TextWindow_setBGColor, (char*)__FILE__);
   newXS((char*)"XMTextWindow::setFGColor",
        XM_TextWindow_setFGColor, (char*)__FILE__);
   newXS((char*)"XMTextBufferWindow::initialize",
        XM_TextBufferWindow_initialize, (char*)__FILE__);
   newXS((char*)"XMTextBufferWindow::getWordWrapColumn",
        XM_TextBufferWindow_getWordWrapColumn, (char*)__FILE__);
   newXS((char*)"XMTextBufferWindow::setWordWrapColumn",
        XM_TextBufferWindow_setWordWrapColumn, (char*)__FILE__);
   newXS((char*)"XMPlugin::initialize",
        XM_Plugin_initialize, (char*)__FILE__);
   newXS((char*)"XMPlugin::call",
        XM_Plugin_call, (char*)__FILE__);
   newXS((char*)"XMConnection::initialize",
        XM_Connection_initialize, (char*)__FILE__);
   newXS((char*)"XMConnection::open",
        XM_Connection_open, (char*)__FILE__);
   newXS((char*)"XMConnection::send",
        XM_Connection_send, (char*)__FILE__);
   newXS((char*)"XMConnection::close",
        XM_Connection_close, (char*)__FILE__);
   newXS((char*)"XMConnection::setInputEncoding",
        XM_Connection_setInputEncoding, (char*)__FILE__);
   newXS((char*)"XMConnection::setOutputEncoding",
        XM_Connection_setOutputEncoding, (char*)__FILE__);
   newXS((char*)"XMInputLine::getCursorX",
        XM_InputLine_getCursorX, (char*)__FILE__);
   newXS((char*)"XMInputLine::getCursorY",
        XM_InputLine_getCursorY, (char*)__FILE__);
   newXS((char*)"XMInputLine::setCursorX",
        XM_InputLine_setCursorX, (char*)__FILE__);
   newXS((char*)"XMInputLine::setCursorY",
        XM_InputLine_setCursorY, (char*)__FILE__);
   newXS((char*)"XMInputLine::getText",
        XM_InputLine_getText, (char*)__FILE__);
   newXS((char*)"XMInputLine::setText",
        XM_InputLine_setText, (char*)__FILE__);
   newXS((char*)"XM::ansiToColored",
        XM_ansiToColored, (char*)__FILE__);
   newXS((char*)"XM::ansiToRaw",
        XM_ansiToRaw, (char*)__FILE__);
   newXS((char*)"XM::echoMode",
        XM_echoMode, (char*)__FILE__);
   newXS((char*)"XM::getActiveWindow",
        XM_getActiveWindow, (char*)__FILE__);
   newXS((char*)"XM::getFocusedInputLine",
        XM_getFocusedInputLine, (char*)__FILE__);
   newXS((char*)"XM::mdiWidth",
        XM_mdiWidth, (char*)__FILE__);
   newXS((char*)"XM::mdiHeight",
        XM_mdiHeight, (char*)__FILE__);
   newXS((char*)"XM::playAudio",
        XM_playAudio, (char*)__FILE__);
   newXS((char*)"XM::resetStatusMsg",
        XM_resetStatusMsg, (char*)__FILE__);
   newXS((char*)"XM::send",
        XM_send, (char*)__FILE__);
   newXS((char*)"XM::setStatusMsg",
        XM_setStatusMsg, (char*)__FILE__);
   newXS((char*)"XM::showError",
        XM_showError, (char*)__FILE__);

    // ... this is a std function in python 
    newXS((char *)"XM::weaken",
	  XM_weaken , (char *)__FILE__); 
  }
}

/////////////////////////////////////////////////////////////////////
// Implementation class PerlInterpret


PerlInterpret::PerlInterpret(GuiScriptingWrapper *callBack):
  callBack(callBack)
{
  currentCallBack = callBack;

  perlInt = perl_alloc();
  
  if (!perlInt)
    exit(42);

  PL_perl_destruct_level = 1;

  perl_construct(perlInt);
  const char *args[]={"xperlmud",
		      "-w",
		      "-e", ""
  };
  int ret = perl_parse(perlInt,xs_init,4,(char **)args,0);
  if(!ret)
    perl_run(perlInt);
  else 
    exit(23);

#ifndef SCRIPTDEVEL
# ifndef NO_MULTILINE_STRING
  printf("evaluating sysinit (multi-line string):\n");
  eval_pv(SYSINIT, true);
# else
  printf("evaluating sysinit (no multi-line string):\n");
  int i=0;
  int sum=0;
  while(script[i] != NULL) {
    sum += strlen(script[i]);
    ++i;
  }
  char *commandString = new char[sum+1];
  i=0;
  int c=0;
  while(script[i] != NULL) {
    int y=0;
    while(script[i][y] != 0) {
      commandString[c] = script[i][y];
      ++y; ++c;
    }
    ++i;
  }
  commandString[c] = 0;
  eval_pv(commandString, false);

  delete[] commandString;
# endif
#else
  printf("evaluating sysinit (FLEXIBLE):\n");
  eval_pv("do 'sysinit.pl';", true);
#endif
  //  STRLEN n_a;
  //  printf("finished.\"%s\" %d\n", SvPV(get_sv("@", FALSE), n_a), n_a);
}

PerlInterpret::~PerlInterpret() {
  currentCallBack = callBack;

  perl_destruct(perlInt);
  perl_free(perlInt);
}

void PerlInterpret::setCallback(GuiScriptingWrapper *cB) {
  currentCallBack = callBack = cB;
}
  
  
void PerlInterpret::textEntered(const char * const text, int length) {
    currentCallBack = callBack;


  dSP;
  
  ENTER;
  SAVETMPS;
  PUSHMARK(SP);
  SV * sv=newSVpv(text, length);
  SvUTF8_on(sv);
  XPUSHs(sv_2mortal(sv));
  PUTBACK;

  call_pv("::wrap_onTextEntered",G_DISCARD);

  SPAGAIN;

  PUTBACK;
  FREETMPS;
  LEAVE;

}

// TODO
void PerlInterpret::addIncludeDir(const char * const inc) {
  currentCallBack = callBack;
  const char *args[]={inc,0};

  ENTER;
  SAVETMPS;
  perl_call_argv("::addIncludeDir",G_DISCARD,(char **)args);
  FREETMPS;
  LEAVE;
}

void PerlInterpret::textReceived(const char * const text, int length, int id) {
  currentCallBack = callBack;

  dSP;

  ENTER;
  SAVETMPS;
  PUSHMARK(SP);
  SV * sv=newSVpv(text, length);
  SvUTF8_on(sv);
  XPUSHs(sv_2mortal(sv));
  XPUSHs(sv_2mortal(newSViv(id)));
  PUTBACK;

  call_pv("::wrap_onTextReceived",G_DISCARD);

  SPAGAIN;

  PUTBACK;
  FREETMPS;
  LEAVE;

}

void PerlInterpret::timer() {
  currentCallBack = callBack;

  dSP;

  ENTER;
  SAVETMPS;
  PUSHMARK(SP);

  PUTBACK;

  call_pv("::wrap_onTimer",G_DISCARD);

  SPAGAIN;

  PUTBACK;
  FREETMPS;
  LEAVE;
}

// TODO
void PerlInterpret::connectionEstablished(int id) {
  currentCallBack = callBack;
  char ids[25];
  snprintf(ids,sizeof(ids),"%d",id);
  char *args[]={ids,0};

  ENTER;
  SAVETMPS;
  perl_call_argv("::wrap_onConnectionEstablished",G_DISCARD,args);
  FREETMPS;
  LEAVE;
}

// TODO
void PerlInterpret::connectionDropped(int id) {
  currentCallBack = callBack;
  char ids[25];
  snprintf(ids,sizeof(ids),"%d",id);
  char *args[]={ids,0};

  ENTER;
  SAVETMPS;
  perl_call_argv("::wrap_onConnectionDropped",G_DISCARD,args);
  FREETMPS;
  LEAVE;
}

// TODO
void PerlInterpret::echo(bool state, int id) {
  currentCallBack = callBack;
  char ids[25];
  snprintf(ids,sizeof(ids),"%d",id);
  const char *args[]={state?"1":"0",const_cast<const char *>(ids),0};
  
  ENTER;
  SAVETMPS;
  perl_call_argv("wrap_onEcho",G_DISCARD,(char **)args);
  FREETMPS;
  LEAVE;
}

// TODO
bool PerlInterpret::keyPressed(const char * const key, 
			       const char * const ascii) {
  bool ret;
  dSP;
#ifdef FIXWARN
  if (false) { Perl___notused+=0; }
#endif
  currentCallBack = callBack;
  const char *args[]={key,ascii,0};

  ENTER;
  SAVETMPS;

  //  PUSHMARK(SP) ;
  //  PUTBACK;

  int count = perl_call_argv("::wrap_onKeyPressed",G_SCALAR,(char **)args);
  if(count != 1)
     croak("Big trouble\n") ;
  
  SPAGAIN;
  // dont know if this breaks anything, but the next
  // line doesnt work with gcc 3.3 any more (braced groups)
  //   ret = (POPi != 0);
  SV* pop = POPs;
  int popi = SvIV(pop);
  ret = (popi != 0);

  PUTBACK;
  FREETMPS;
  LEAVE;

  return ret;
}

// TODO
void PerlInterpret::mouseDown(int id,int x,int y) {
  currentCallBack = callBack;

  char ids[25];
  char xs[25];
  char ys[25];
  snprintf(ids,sizeof(ids),"%d",id);
  snprintf(xs,sizeof(xs),"%d",x);
  snprintf(ys,sizeof(ys),"%d",y);

  const char *args[]={ids,xs,ys,0};
    
  ENTER;
  SAVETMPS;
  perl_call_argv("::wrap_mouseDown",G_DISCARD,(char **)args);
  FREETMPS;
  LEAVE;
}

// TODO
void PerlInterpret::mouseDrag(int id,int x,int y) {
  currentCallBack = callBack;

  char ids[25];
  char xs[25];
  char ys[25];
  snprintf(ids,sizeof(ids),"%d",id);
  snprintf(xs,sizeof(xs),"%d",x);
  snprintf(ys,sizeof(ys),"%d",y);

  const char *args[]={ids,xs,ys,0};
    
  ENTER;
  SAVETMPS;
  perl_call_argv("::wrap_mouseDrag",G_DISCARD,(char **)args);
  FREETMPS;
  LEAVE;
}

// TODO
void PerlInterpret::mouseUp(int id,int x,int y) {
  currentCallBack = callBack;

  char ids[25];
  char xs[25];
  char ys[25];
  snprintf(ids,sizeof(ids),"%d",id);
  snprintf(xs,sizeof(xs),"%d",x);
  snprintf(ys,sizeof(ys),"%d",y);

  const char *args[]={ids,xs,ys,0};
    
  ENTER;
  SAVETMPS;
  perl_call_argv("::wrap_mouseUp",G_DISCARD,(char **)args);
  FREETMPS;
  LEAVE;
}

const char * PerlInterpret::pluginCall(int id,int function, const char * const args, int length) {
  currentCallBack = callBack;
  dSP;

  ENTER;
  SAVETMPS;
  PUSHMARK(SP);
  XPUSHs(sv_2mortal(newSViv(id)));
  XPUSHs(sv_2mortal(newSViv(function)));
  if (args) {
      SV * sv=newSVpv(args,length);
      SvUTF8_on(sv);
      XPUSHs(sv_2mortal(sv));
  } else {
      XPUSHs(&PL_sv_undef);
  }
  PUTBACK;

  int count = call_pv("::wrap_pluginCall",G_SCALAR);

  SPAGAIN;

  if (count != 1)
    croak("Big trouble\n") ;

  char * retval=NULL;
  SV * rval=POPs;
  if (SvPOK(rval)) {
      STRLEN len;
      char *retval_temp = SvPV(rval,len);

      char * retval=new char[len+1];
      strncpy(retval,retval_temp,len);
      retval[len]=0;
  }
  PUTBACK;
  FREETMPS;
  LEAVE;
  return retval;
}


