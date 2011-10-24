// -*- c++ -*-
/**
 * Code fragments stolen from the mcl project. I didn't
 * find out who wrote the stuff, cause they don't write
 * any names into their filez. (like we do in some of ours :)
 */

#include "XMPython.h"

#define NO_MULTILINE_STRING 1
#ifndef NO_MULTILINE_STRING
#include "sysinit_py.h"
#else
#include "sysinit_pyf.h"
#endif

#include "../GuiScriptingBindings.h"

#include <kglobal.h>
#include <kstandarddirs.h>
#include <qtextcodec.h>


// TODO: remove
#include <iostream>
using std::cout;
using std::endl;

static GuiScriptingBindings *currentCallBack;

extern "C" {

  PyObject *PXM_Window_close(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_close(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_getPositionX(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_Window_getPositionX(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_Window_getPositionY(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_Window_getPositionY(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_Window_getSizeX(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_Window_getSizeX(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_Window_getSizeY(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_Window_getSizeY(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_Window_hide(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_hide(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_hideCaption(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_hideCaption(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_isValid(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    bool ret = currentCallBack->
      XM_Window_isValid(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_Window_lower(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_lower(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_maximize(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_maximize(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_minimize(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_minimize(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_move(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int x;
    int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iii"), &id, &x, &y))
      return NULL;

    currentCallBack->
      XM_Window_move(id,x,y);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_raise(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_raise(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_resize(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int x;
    int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iii"), &id, &x, &y))
      return NULL;

    currentCallBack->
      XM_Window_resize(id,x,y);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_setTitle(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iO"), &id, &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    currentCallBack->
      XM_Window_setTitle(id,qstring);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_show(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_show(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Window_showCaption(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Window_showCaption(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_initialize(PyObject * /* unused: self */, PyObject * /* unused: args */) {

    int ret = currentCallBack->
      XM_TextWindow_initialize();

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_clear(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_clear(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_clearEOL(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_clearEOL(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_clearBOL(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_clearBOL(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_clearEOS(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_clearEOS(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_clearBOS(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_clearBOS(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_clearLine(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_clearLine(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_disableMouseEvents(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_disableMouseEvents(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_enableMouseEvents(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_enableMouseEvents(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_getCharAt(PyObject * /* unused: self */, PyObject *args) {
    int id;
    unsigned int x;
    unsigned int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iii"), &id, &x, &y))
      return NULL;

    char ret = currentCallBack->
      XM_TextWindow_getCharAt(id,x,y);

    return Py_BuildValue(const_cast<char *>("b"), ret);
  }

  PyObject *PXM_TextWindow_getColumns(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_TextWindow_getColumns(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_getCursorX(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_TextWindow_getCursorX(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_getCursorY(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_TextWindow_getCursorY(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_getFGColorAt(PyObject * /* unused: self */, PyObject *args) {
    int id;
    unsigned int x;
    unsigned int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iii"), &id, &x, &y))
      return NULL;

    int ret = currentCallBack->
      XM_TextWindow_getFGColorAt(id,x,y);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_getBGColorAt(PyObject * /* unused: self */, PyObject *args) {
    int id;
    unsigned int x;
    unsigned int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iii"), &id, &x, &y))
      return NULL;

    int ret = currentCallBack->
      XM_TextWindow_getBGColorAt(id,x,y);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_getLines(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_TextWindow_getLines(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_newline(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_newline(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_printRaw(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iO"), &id, &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    currentCallBack->
      XM_TextWindow_printRaw(id,qstring);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_print(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iO"), &id, &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    currentCallBack->
      XM_TextWindow_print(id,qstring);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_resetAttributes(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_TextWindow_resetAttributes(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_resizeChars(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int x;
    int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iii"), &id, &x, &y))
      return NULL;

    currentCallBack->
      XM_TextWindow_resizeChars(id,x,y);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_scrollColumns(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int cols;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &cols))
      return NULL;

    currentCallBack->
      XM_TextWindow_scrollColumns(id,cols);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_scrollLines(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int lines;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &lines))
      return NULL;

    currentCallBack->
      XM_TextWindow_scrollLines(id,lines);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setBold(PyObject * /* unused: self */, PyObject *args) {
    int id;
    bool bold;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &bold))
      return NULL;

    currentCallBack->
      XM_TextWindow_setBold(id,bold);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setBlinking(PyObject * /* unused: self */, PyObject *args) {
    int id;
    bool bold;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &bold))
      return NULL;

    currentCallBack->
      XM_TextWindow_setBlinking(id,bold);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setCursor(PyObject * /* unused: self */, PyObject *args) {
    int id;
    unsigned int x;
    unsigned int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iii"), &id, &x, &y))
      return NULL;

    currentCallBack->
      XM_TextWindow_setCursor(id,x,y);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setDefaultBGColor(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int color;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &color))
      return NULL;

    currentCallBack->
      XM_TextWindow_setDefaultBGColor(id,color);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setDefaultFGColor(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int color;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &color))
      return NULL;

    currentCallBack->
      XM_TextWindow_setDefaultFGColor(id,color);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setFont(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* string = NULL;
    int size;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iOi"), &id, &string, &size))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    bool ret = currentCallBack->
      XM_TextWindow_setFont(id,qstring,size);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextWindow_setIntensive(PyObject * /* unused: self */, PyObject *args) {
    int id;
    bool bold;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &bold))
      return NULL;

    currentCallBack->
      XM_TextWindow_setIntensive(id,bold);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setReverse(PyObject * /* unused: self */, PyObject *args) {
    int id;
    bool bold;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &bold))
      return NULL;

    currentCallBack->
      XM_TextWindow_setReverse(id,bold);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setUnderline(PyObject * /* unused: self */, PyObject *args) {
    int id;
    bool bold;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &bold))
      return NULL;

    currentCallBack->
      XM_TextWindow_setUnderline(id,bold);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setBGColor(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int color;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &color))
      return NULL;

    currentCallBack->
      XM_TextWindow_setBGColor(id,color);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextWindow_setFGColor(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int color;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &color))
      return NULL;

    currentCallBack->
      XM_TextWindow_setFGColor(id,color);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_TextBufferWindow_initialize(PyObject * /* unused: self */, PyObject * /* unused: args */) {

    int ret = currentCallBack->
      XM_TextBufferWindow_initialize();

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextBufferWindow_getWordWrapColumn(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_TextBufferWindow_getWordWrapColumn(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_TextBufferWindow_setWordWrapColumn(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int col;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &col))
      return NULL;

    currentCallBack->
      XM_TextBufferWindow_setWordWrapColumn(id,col);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Plugin_initialize(PyObject * /* unused: self */, PyObject *args) {
    PyObject* libname = NULL;
    PyObject* classname = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("OO"), &libname, &classname))
      return NULL;

    QString qlibname;
    if(libname == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* libnameUni;
      if(PyUnicode_Check(libname)) {
        libnameUni = libname;
      } else {
        libnameUni = PyUnicode_FromObject(libname);
      }
      if(libnameUni == NULL) {
        return NULL;
      }
      int libnameLen = PyUnicode_GET_DATA_SIZE(libnameUni) / sizeof(Py_UNICODE);
      qlibname = QString((QChar*)NULL, libnameLen);
      Py_UNICODE* plibname = PyUnicode_AS_UNICODE(libnameUni);
      for(int i=0; i<libnameLen; ++i) {
        qlibname.ref(i) = QChar(plibname[i]);
      }
    }

    QString qclassname;
    if(classname == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* classnameUni;
      if(PyUnicode_Check(classname)) {
        classnameUni = classname;
      } else {
        classnameUni = PyUnicode_FromObject(classname);
      }
      if(classnameUni == NULL) {
        return NULL;
      }
      int classnameLen = PyUnicode_GET_DATA_SIZE(classnameUni) / sizeof(Py_UNICODE);
      qclassname = QString((QChar*)NULL, classnameLen);
      Py_UNICODE* pclassname = PyUnicode_AS_UNICODE(classnameUni);
      for(int i=0; i<classnameLen; ++i) {
        qclassname.ref(i) = QChar(pclassname[i]);
      }
    }

    int ret = currentCallBack->
      XM_Plugin_initialize(qlibname,qclassname);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_Plugin_call(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int fnum;
    PyObject* param = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iiO"), &id, &fnum, &param))
      return NULL;

    QString qparam;
    if(param == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* paramUni;
      if(PyUnicode_Check(param)) {
        paramUni = param;
      } else {
        paramUni = PyUnicode_FromObject(param);
      }
      if(paramUni == NULL) {
        return NULL;
      }
      int paramLen = PyUnicode_GET_DATA_SIZE(paramUni) / sizeof(Py_UNICODE);
      qparam = QString((QChar*)NULL, paramLen);
      Py_UNICODE* pparam = PyUnicode_AS_UNICODE(paramUni);
      for(int i=0; i<paramLen; ++i) {
        qparam.ref(i) = QChar(pparam[i]);
      }
    }

    QString ret = currentCallBack->
      XM_Plugin_call(id,fnum,qparam);


    Py_UNICODE* retUni = new Py_UNICODE[ret.length()];
    {for(unsigned int i=0; i<ret.length(); ++i)
      retUni[i] = ret.at(i).unicode();
    }
    return Py_BuildValue(const_cast<char *>("u#"),
                         retUni, ret.length());
    delete[] retUni;
}  PyObject *PXM_Connection_initialize(PyObject * /* unused: self */, PyObject *args) {
    PyObject* host = NULL;
    int port;
    PyObject* onConnect = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("Oi|O"), &host, &port, &onConnect))
      return NULL;

    QString qhost;
    if(host == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* hostUni;
      if(PyUnicode_Check(host)) {
        hostUni = host;
      } else {
        hostUni = PyUnicode_FromObject(host);
      }
      if(hostUni == NULL) {
        return NULL;
      }
      int hostLen = PyUnicode_GET_DATA_SIZE(hostUni) / sizeof(Py_UNICODE);
      qhost = QString((QChar*)NULL, hostLen);
      Py_UNICODE* phost = PyUnicode_AS_UNICODE(hostUni);
      for(int i=0; i<hostLen; ++i) {
        qhost.ref(i) = QChar(phost[i]);
      }
    }

    QString qonConnect;
    if(onConnect == NULL) { // unspecified argument
      qonConnect = "";
    } else {
      PyObject* onConnectUni;
      if(PyUnicode_Check(onConnect)) {
        onConnectUni = onConnect;
      } else {
        onConnectUni = PyUnicode_FromObject(onConnect);
      }
      if(onConnectUni == NULL) {
        return NULL;
      }
      int onConnectLen = PyUnicode_GET_DATA_SIZE(onConnectUni) / sizeof(Py_UNICODE);
      qonConnect = QString((QChar*)NULL, onConnectLen);
      Py_UNICODE* ponConnect = PyUnicode_AS_UNICODE(onConnectUni);
      for(int i=0; i<onConnectLen; ++i) {
        qonConnect.ref(i) = QChar(ponConnect[i]);
      }
    }

    int ret = currentCallBack->
      XM_Connection_initialize(qhost,port,qonConnect);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_Connection_open(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* host = NULL;
    int port;
    PyObject* onConnect = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iOi|O"), &id, &host, &port, &onConnect))
      return NULL;

    QString qhost;
    if(host == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* hostUni;
      if(PyUnicode_Check(host)) {
        hostUni = host;
      } else {
        hostUni = PyUnicode_FromObject(host);
      }
      if(hostUni == NULL) {
        return NULL;
      }
      int hostLen = PyUnicode_GET_DATA_SIZE(hostUni) / sizeof(Py_UNICODE);
      qhost = QString((QChar*)NULL, hostLen);
      Py_UNICODE* phost = PyUnicode_AS_UNICODE(hostUni);
      for(int i=0; i<hostLen; ++i) {
        qhost.ref(i) = QChar(phost[i]);
      }
    }

    QString qonConnect;
    if(onConnect == NULL) { // unspecified argument
      qonConnect = "";
    } else {
      PyObject* onConnectUni;
      if(PyUnicode_Check(onConnect)) {
        onConnectUni = onConnect;
      } else {
        onConnectUni = PyUnicode_FromObject(onConnect);
      }
      if(onConnectUni == NULL) {
        return NULL;
      }
      int onConnectLen = PyUnicode_GET_DATA_SIZE(onConnectUni) / sizeof(Py_UNICODE);
      qonConnect = QString((QChar*)NULL, onConnectLen);
      Py_UNICODE* ponConnect = PyUnicode_AS_UNICODE(onConnectUni);
      for(int i=0; i<onConnectLen; ++i) {
        qonConnect.ref(i) = QChar(ponConnect[i]);
      }
    }

    currentCallBack->
      XM_Connection_open(id,qhost,port,qonConnect);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Connection_send(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iO"), &id, &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    currentCallBack->
      XM_Connection_send(id,qstring);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Connection_close(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    currentCallBack->
      XM_Connection_close(id);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Connection_setInputEncoding(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* enc = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iO"), &id, &enc))
      return NULL;

    QString qenc;
    if(enc == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* encUni;
      if(PyUnicode_Check(enc)) {
        encUni = enc;
      } else {
        encUni = PyUnicode_FromObject(enc);
      }
      if(encUni == NULL) {
        return NULL;
      }
      int encLen = PyUnicode_GET_DATA_SIZE(encUni) / sizeof(Py_UNICODE);
      qenc = QString((QChar*)NULL, encLen);
      Py_UNICODE* penc = PyUnicode_AS_UNICODE(encUni);
      for(int i=0; i<encLen; ++i) {
        qenc.ref(i) = QChar(penc[i]);
      }
    }

    currentCallBack->
      XM_Connection_setInputEncoding(id,qenc);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_Connection_setOutputEncoding(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* enc = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iO"), &id, &enc))
      return NULL;

    QString qenc;
    if(enc == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* encUni;
      if(PyUnicode_Check(enc)) {
        encUni = enc;
      } else {
        encUni = PyUnicode_FromObject(enc);
      }
      if(encUni == NULL) {
        return NULL;
      }
      int encLen = PyUnicode_GET_DATA_SIZE(encUni) / sizeof(Py_UNICODE);
      qenc = QString((QChar*)NULL, encLen);
      Py_UNICODE* penc = PyUnicode_AS_UNICODE(encUni);
      for(int i=0; i<encLen; ++i) {
        qenc.ref(i) = QChar(penc[i]);
      }
    }

    currentCallBack->
      XM_Connection_setOutputEncoding(id,qenc);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_InputLine_getCursorX(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_InputLine_getCursorX(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_InputLine_getCursorY(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    int ret = currentCallBack->
      XM_InputLine_getCursorY(id);

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_InputLine_setCursorX(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int x;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &x))
      return NULL;

    currentCallBack->
      XM_InputLine_setCursorX(id,x);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_InputLine_setCursorY(PyObject * /* unused: self */, PyObject *args) {
    int id;
    int y;
    if(!PyArg_ParseTuple(args, const_cast<char *>("ii"), &id, &y))
      return NULL;

    currentCallBack->
      XM_InputLine_setCursorY(id,y);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_InputLine_getText(PyObject * /* unused: self */, PyObject *args) {
    int id;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &id))
      return NULL;

    QString ret = currentCallBack->
      XM_InputLine_getText(id);


    Py_UNICODE* retUni = new Py_UNICODE[ret.length()];
    {for(unsigned int i=0; i<ret.length(); ++i)
      retUni[i] = ret.at(i).unicode();
    }
    return Py_BuildValue(const_cast<char *>("u#"),
                         retUni, ret.length());
    delete[] retUni;
}  PyObject *PXM_InputLine_setText(PyObject * /* unused: self */, PyObject *args) {
    int id;
    PyObject* text = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("iO"), &id, &text))
      return NULL;

    QString qtext;
    if(text == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* textUni;
      if(PyUnicode_Check(text)) {
        textUni = text;
      } else {
        textUni = PyUnicode_FromObject(text);
      }
      if(textUni == NULL) {
        return NULL;
      }
      int textLen = PyUnicode_GET_DATA_SIZE(textUni) / sizeof(Py_UNICODE);
      qtext = QString((QChar*)NULL, textLen);
      Py_UNICODE* ptext = PyUnicode_AS_UNICODE(textUni);
      for(int i=0; i<textLen; ++i) {
        qtext.ref(i) = QChar(ptext[i]);
      }
    }

    currentCallBack->
      XM_InputLine_setText(id,qtext);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_ansiToColored(PyObject * /* unused: self */, PyObject *args) {
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("O"), &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    QString ret = currentCallBack->
      XM_ansiToColored(qstring);


    Py_UNICODE* retUni = new Py_UNICODE[ret.length()];
    {for(unsigned int i=0; i<ret.length(); ++i)
      retUni[i] = ret.at(i).unicode();
    }
    return Py_BuildValue(const_cast<char *>("u#"),
                         retUni, ret.length());
    delete[] retUni;
}  PyObject *PXM_ansiToRaw(PyObject * /* unused: self */, PyObject *args) {
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("O"), &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    QString ret = currentCallBack->
      XM_ansiToRaw(qstring);


    Py_UNICODE* retUni = new Py_UNICODE[ret.length()];
    {for(unsigned int i=0; i<ret.length(); ++i)
      retUni[i] = ret.at(i).unicode();
    }
    return Py_BuildValue(const_cast<char *>("u#"),
                         retUni, ret.length());
    delete[] retUni;
}  PyObject *PXM_echoMode(PyObject * /* unused: self */, PyObject *args) {
    bool state;
    if(!PyArg_ParseTuple(args, const_cast<char *>("i"), &state))
      return NULL;

    currentCallBack->
      XM_echoMode(state);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_getActiveWindow(PyObject * /* unused: self */, PyObject * /* unused: args */) {

    int ret = currentCallBack->
      XM_getActiveWindow();

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_getFocusedInputLine(PyObject * /* unused: self */, PyObject * /* unused: args */) {

    int ret = currentCallBack->
      XM_getFocusedInputLine();

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_mdiWidth(PyObject * /* unused: self */, PyObject * /* unused: args */) {

    int ret = currentCallBack->
      XM_mdiWidth();

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_mdiHeight(PyObject * /* unused: self */, PyObject * /* unused: args */) {

    int ret = currentCallBack->
      XM_mdiHeight();

    return Py_BuildValue(const_cast<char *>("i"), ret);
  }

  PyObject *PXM_playAudio(PyObject * /* unused: self */, PyObject *args) {
    PyObject* filename = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("O"), &filename))
      return NULL;

    QString qfilename;
    if(filename == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* filenameUni;
      if(PyUnicode_Check(filename)) {
        filenameUni = filename;
      } else {
        filenameUni = PyUnicode_FromObject(filename);
      }
      if(filenameUni == NULL) {
        return NULL;
      }
      int filenameLen = PyUnicode_GET_DATA_SIZE(filenameUni) / sizeof(Py_UNICODE);
      qfilename = QString((QChar*)NULL, filenameLen);
      Py_UNICODE* pfilename = PyUnicode_AS_UNICODE(filenameUni);
      for(int i=0; i<filenameLen; ++i) {
        qfilename.ref(i) = QChar(pfilename[i]);
      }
    }

    currentCallBack->
      XM_playAudio(qfilename);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_resetStatusMsg(PyObject * /* unused: self */, PyObject * /* unused: args */) {

    currentCallBack->
      XM_resetStatusMsg();

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_send(PyObject * /* unused: self */, PyObject *args) {
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("O"), &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    currentCallBack->
      XM_send(qstring);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_setStatusMsg(PyObject * /* unused: self */, PyObject *args) {
    PyObject* message = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("O"), &message))
      return NULL;

    QString qmessage;
    if(message == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* messageUni;
      if(PyUnicode_Check(message)) {
        messageUni = message;
      } else {
        messageUni = PyUnicode_FromObject(message);
      }
      if(messageUni == NULL) {
        return NULL;
      }
      int messageLen = PyUnicode_GET_DATA_SIZE(messageUni) / sizeof(Py_UNICODE);
      qmessage = QString((QChar*)NULL, messageLen);
      Py_UNICODE* pmessage = PyUnicode_AS_UNICODE(messageUni);
      for(int i=0; i<messageLen; ++i) {
        qmessage.ref(i) = QChar(pmessage[i]);
      }
    }

    currentCallBack->
      XM_setStatusMsg(qmessage);

    Py_INCREF(Py_None);
    return Py_None;
  }

  PyObject *PXM_showError(PyObject * /* unused: self */, PyObject *args) {
    PyObject* string = NULL;
    if(!PyArg_ParseTuple(args, const_cast<char *>("O"), &string))
      return NULL;

    QString qstring;
    if(string == NULL) { // unspecified argument
      return NULL;
    } else {
      PyObject* stringUni;
      if(PyUnicode_Check(string)) {
        stringUni = string;
      } else {
        stringUni = PyUnicode_FromObject(string);
      }
      if(stringUni == NULL) {
        return NULL;
      }
      int stringLen = PyUnicode_GET_DATA_SIZE(stringUni) / sizeof(Py_UNICODE);
      qstring = QString((QChar*)NULL, stringLen);
      Py_UNICODE* pstring = PyUnicode_AS_UNICODE(stringUni);
      for(int i=0; i<stringLen; ++i) {
        qstring.ref(i) = QChar(pstring[i]);
      }
    }

    currentCallBack->
      XM_showError(qstring);

    Py_INCREF(Py_None);
    return Py_None;
  }


  static PyMethodDef XM_Methods[] = {
    {const_cast<char *>("Window_close"), 	PXM_Window_close, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_getPositionX"), 	PXM_Window_getPositionX, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_getPositionY"), 	PXM_Window_getPositionY, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_getSizeX"), 	PXM_Window_getSizeX, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_getSizeY"), 	PXM_Window_getSizeY, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_hide"), 	PXM_Window_hide, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_hideCaption"), 	PXM_Window_hideCaption, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_isValid"), 	PXM_Window_isValid, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_lower"), 	PXM_Window_lower, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_maximize"), 	PXM_Window_maximize, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_minimize"), 	PXM_Window_minimize, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_move"), 	PXM_Window_move, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_lift"), 	PXM_Window_raise, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_resize"), 	PXM_Window_resize, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_setTitle"), 	PXM_Window_setTitle, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_show"), 	PXM_Window_show, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Window_showCaption"), 	PXM_Window_showCaption, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_initialize"), 	PXM_TextWindow_initialize, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_clear"), 	PXM_TextWindow_clear, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_clearEOL"), 	PXM_TextWindow_clearEOL, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_clearBOL"), 	PXM_TextWindow_clearBOL, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_clearEOS"), 	PXM_TextWindow_clearEOS, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_clearBOS"), 	PXM_TextWindow_clearBOS, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_clearLine"), 	PXM_TextWindow_clearLine, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_disableMouseEvents"), 	PXM_TextWindow_disableMouseEvents, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_enableMouseEvents"), 	PXM_TextWindow_enableMouseEvents, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_getCharAt"), 	PXM_TextWindow_getCharAt, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_getColumns"), 	PXM_TextWindow_getColumns, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_getCursorX"), 	PXM_TextWindow_getCursorX, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_getCursorY"), 	PXM_TextWindow_getCursorY, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_getFGColorAt"), 	PXM_TextWindow_getFGColorAt, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_getBGColorAt"), 	PXM_TextWindow_getBGColorAt, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_getLines"), 	PXM_TextWindow_getLines, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_newline"), 	PXM_TextWindow_newline, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_writeRaw"), 	PXM_TextWindow_printRaw, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_write"), 	PXM_TextWindow_print, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_resetAttributes"), 	PXM_TextWindow_resetAttributes, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_resizeChars"), 	PXM_TextWindow_resizeChars, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_scrollColumns"), 	PXM_TextWindow_scrollColumns, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_scrollLines"), 	PXM_TextWindow_scrollLines, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setBold"), 	PXM_TextWindow_setBold, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setBlinking"), 	PXM_TextWindow_setBlinking, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setCursor"), 	PXM_TextWindow_setCursor, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setDefaultBGColor"), 	PXM_TextWindow_setDefaultBGColor, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setDefaultFGColor"), 	PXM_TextWindow_setDefaultFGColor, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setFont"), 	PXM_TextWindow_setFont, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setIntensive"), 	PXM_TextWindow_setIntensive, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setReverse"), 	PXM_TextWindow_setReverse, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setUnderline"), 	PXM_TextWindow_setUnderline, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setBGColor"), 	PXM_TextWindow_setBGColor, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextWindow_setFGColor"), 	PXM_TextWindow_setFGColor, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextBufferWindow_initialize"), 	PXM_TextBufferWindow_initialize, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextBufferWindow_getWordWrapColumn"), 	PXM_TextBufferWindow_getWordWrapColumn, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("TextBufferWindow_setWordWrapColumn"), 	PXM_TextBufferWindow_setWordWrapColumn, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Plugin_initialize"), 	PXM_Plugin_initialize, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Plugin_call"), 	PXM_Plugin_call, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Connection_initialize"), 	PXM_Connection_initialize, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Connection_open"), 	PXM_Connection_open, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Connection_send"), 	PXM_Connection_send, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Connection_close"), 	PXM_Connection_close, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Connection_setInputEncoding"), 	PXM_Connection_setInputEncoding, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("Connection_setOutputEncoding"), 	PXM_Connection_setOutputEncoding, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("InputLine_getCursorX"), 	PXM_InputLine_getCursorX, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("InputLine_getCursorY"), 	PXM_InputLine_getCursorY, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("InputLine_setCursorX"), 	PXM_InputLine_setCursorX, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("InputLine_setCursorY"), 	PXM_InputLine_setCursorY, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("InputLine_getText"), 	PXM_InputLine_getText, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("InputLine_setText"), 	PXM_InputLine_setText, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("ansiToColored"), 	PXM_ansiToColored, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("ansiToRaw"), 	PXM_ansiToRaw, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("echoMode"), 	PXM_echoMode, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("getActiveWindow"), 	PXM_getActiveWindow, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("getFocusedInputLine"), 	PXM_getFocusedInputLine, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("mdiWidth"), 	PXM_mdiWidth, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("mdiHeight"), 	PXM_mdiHeight, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("playAudio"), 	PXM_playAudio, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("resetStatusMsg"), 	PXM_resetStatusMsg, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("send"), 	PXM_send, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("setStatusMsg"), 	PXM_setStatusMsg, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {const_cast<char *>("showError"), 	PXM_showError, 	METH_VARARGS, const_cast<char *>("Not documented")},
    {NULL, NULL, 0, NULL}
  };
  
  
}



XMPython::XMPython(QObject* parent,
		   const char* name):
  XMScripting(parent,name),callBack(NULL) {
  qDebug("XPPython::XMPython");
}

XMPython::~XMPython() {
  qDebug("XPPython::XMPython");
  currentCallBack = callBack;
  //  cleanup python resources
  if(Py_IsInitialized()) {
    cout << "Finalizing Python" << endl;
    Py_Finalize();
    cout << "Finished." << endl;
  }
}

void XMPython::setCallback(GuiScriptingBindings *cB) {
  qDebug("Setting callback");

  callBack=cB;

  currentCallBack = callBack;

 

  // now create all those python resources needed...
  PyObject *module;

  Py_Initialize();


  Py_InitModule(const_cast<char*>("XM"), XM_Methods);

  module = PyImport_AddModule(const_cast<char*>("__main__"));
  globals = PyModule_GetDict(module);
  Py_INCREF(globals);

  PyObject *obj;
#ifndef SCRIPTDEVEL
# ifndef NO_MULTILINE_STRING
  cout << "evaluating sysinit (multi-line string):" <<endl;
  if((obj = PyRun_String(const_cast<char *>(SYSINIT), 
			 Py_file_input, globals, globals))) {
# else
  cout << "evaluating sysinit (no multi-line string):" <<endl;
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
  if((obj = PyRun_String(commandString,
			 Py_file_input, globals, globals))) {
# endif
#else
  cout << "evaluating sysinit (FLEXIBLE):" << endl;
  if((obj = PyRun_String("import sys\nsys.path.append(\".\")\nfrom sysinit import *",
			 Py_file_input, globals, globals))) {
#endif
    Py_DECREF(obj);
  } else {
    PyErr_Print();
  }

#ifndef SCRIPTDEVEL
#ifdef NO_MULTILINE_STRING
  delete[] commandString;
#endif
#endif

  // now search for include paths
  QStringList incPath=KGlobal::dirs()->findDirs("appdata","python");
  
  for (QStringList::Iterator it=incPath.begin();
       it!=incPath.end(); ++it) {
    
    PyObject *obj;
    if((obj = PyRun_String(const_cast<char *>(("sys.path.append(\""+*it+"\")").latin1()),
			   Py_file_input, globals, globals))) {
      Py_DECREF(obj);
    } else {
      PyErr_Print();
    }
  
  }
  

}

void XMPython::textEntered(const QString & text) {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_onTextEntered"));
  PyObject *arglist;
  PyObject *result;

  Py_UNICODE* pytext = convert(text);
  arglist = Py_BuildValue(const_cast<char *>("(u#)"),
			  pytext, text.length());
  delete[] pytext;

  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  if(result != NULL)
    Py_DECREF(result);
}

bool XMPython::keyPressed(const QString & key, const QString & ascii) {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_onKeyPressed"));
  PyObject *arglist;
  PyObject *result;
  
  Py_UNICODE* pykey = convert(key);
  Py_UNICODE* pyascii = convert(ascii);
  arglist = Py_BuildValue(const_cast<char *>("(u#u#)"), 
			  pykey, key.length(), 
			  pyascii, ascii.length());
  delete[] pykey;
  delete[] pyascii;

  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);

  int ret = 0;
  if(result != NULL) {
    ret = (int)PyInt_AsLong(result);
    Py_DECREF(result);
  }

  return ret;
}

void XMPython::textReceived(const QString & line, int id) {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_onTextReceived"));
  PyObject *arglist;
  PyObject *result;
  
  Py_UNICODE* pyline = convert(line);
  arglist = Py_BuildValue(const_cast<char *>("(u#i)"), 
			  pyline, line.length(), id);
  delete[] pyline;

  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  if(result != NULL)
    Py_DECREF(result);
}

void XMPython::timer() {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_onTimer"));

  if(fn == NULL) {
    cout << "didn't find timer" << endl;
    return;
  }

  PyObject *result;
  result = PyEval_CallObject(fn, NULL);
  if(result != NULL)
    Py_DECREF(result);
}

void XMPython::echo(bool state, int id) {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_onEcho"));
  PyObject *arglist;
  PyObject *result;
  
  arglist = Py_BuildValue(const_cast<char *>("(ii)"), state, id);
  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  if(result != NULL)
    Py_DECREF(result);
}

void XMPython::connectionEstablished(int id) {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_onConnectionEstablished"));
  PyObject *arglist;
  PyObject *result;
  
  arglist = Py_BuildValue(const_cast<char *>("(i)"), id);
  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  if(result != NULL)
    Py_DECREF(result);
}

void XMPython::connectionDropped(int id) {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_onConnectionDropped"));
  PyObject *arglist;
  PyObject *result;
  
  arglist = Py_BuildValue(const_cast<char *>("(i)"), id);
  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  if(result != NULL)
    Py_DECREF(result);
}


void XMPython::mouseDown(int id, int x, int y) {
  currentCallBack = callBack;
  
  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_mouseDown"));
  PyObject *arglist;
  PyObject *result;
  
  arglist = Py_BuildValue(const_cast<char *>("(iii)"), id, x, y);
  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  
  if(result != NULL)
    Py_DECREF(result);
}

void XMPython::mouseDrag(int id, int x, int y) {
  currentCallBack = callBack;
  
  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_mouseDrag"));
  PyObject *arglist;
  PyObject *result;
  
  arglist = Py_BuildValue(const_cast<char *>("(iii)"), id, x, y);
  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  
  if(result != NULL)
    Py_DECREF(result);
}

void XMPython::mouseUp(int id, int x, int y) {
  currentCallBack = callBack;
  
  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_mouseUp"));
  PyObject *arglist;
  PyObject *result;
  
  arglist = Py_BuildValue(const_cast<char *>("(iii)"), id, x, y);
  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);
  
  if(result != NULL)
    Py_DECREF(result);
}

QVariant XMPython::pluginCall(int id, int function, const QVariant & args) {
  currentCallBack = callBack;

  PyObject *fn = PyDict_GetItemString
    (globals, const_cast<char *>("wrap_pluginCall"));
  PyObject *arglist;
  PyObject *result;
  
  QString qargs = args.toString();
  Py_UNICODE* pyargs = convert(qargs);
  arglist = Py_BuildValue(const_cast<char *>("(iiu#)"), 
			  id, function, pyargs, qargs.length());
  delete[] pyargs;

  result = PyEval_CallObject(fn, arglist);
  Py_DECREF(arglist);

  char *retString;
  QString ret = "";
  if(result != NULL) {
    retString = PyString_AsString(result);
    if(retString != NULL)
      ret = retString;
    Py_DECREF(result);
  }

  return ret;
}

 
Py_UNICODE* XMPython::convert(const QString& text) {
  Py_UNICODE* buffer = new Py_UNICODE[text.length()];
  for(unsigned int i=0; i<text.length(); ++i) {
    buffer[i] = text.at(i).unicode();
  }
  return buffer;
}
