# Miro - an RSS based video player application
# Copyright (C) 2005-2008 Participatory Culture Foundation
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
#
# In addition, as a special exception, the copyright holders give
# permission to link the code of portions of this program with the OpenSSL
# library.
#
# You must obey the GNU General Public License in all respects for all of
# the code used other than OpenSSL. If you modify file(s) with this
# exception, you may extend this exception to your version of the file(s),
# but you are not obligated to do so. If you do not wish to do so, delete
# this exception statement from your version. If you delete this exception
# statement from all source files in the program, then also delete it here.

"""xulrunnerbrowser -- Pyrex module to implement an embedded XULRunner
broswer.
"""

cdef extern from "Python.h":
    ctypedef struct PyObject
    PyObject* PyObject_CallMethod(PyObject *o, char* name, char* format, ...)
    PyObject* PyObject_CallFunction(PyObject *o, char* format, ...)
    void Py_DECREF(PyObject*)
    void Py_INCREF(PyObject*)

cdef extern from "nscore.h":
    ctypedef unsigned int nsresult
    ctypedef unsigned int PRBool
    cdef enum NS_RESULT_VALUES:
        NS_OK = 0

cdef extern from "MiroBrowserEmbed.h":
    ctypedef void(*focusCallback)(PRBool forward, void* data)
    ctypedef struct MiroBrowserEmbed:
        nsresult (*init)(unsigned long parentWindow, int x, int y, int width, 
                int height)
        nsresult (*destroy)()
        nsresult (*loadURI)(char* uri)
        nsresult (*resize)(int x, int y, int width, int height)
        nsresult (*focus)()
        void (*SetFocusCallback)(focusCallback callback, void* data)
    # Trick Cython into creating constructor and destructor code
    MiroBrowserEmbed *new_MiroBrowserEmbed "new MiroBrowserEmbed" ()
    void del_MiroBrowserEmbed "delete" (MiroBrowserEmbed *rect)
    void addref(MiroBrowserEmbed* browser)
    void release(MiroBrowserEmbed* browser)

cdef extern from "Init.h":
    nsresult init_xulrunner(char* xul_dir, char* app_dir)
    void shutdown_xulrunner()

cdef extern from "pythread.h":
    ctypedef struct PyThreadState
    PyThreadState *PyEval_SaveThread()
    void PyEval_RestoreThread(PyThreadState *_save)

def initialize(xul_dir, app_dir):
    cdef nsresult rv
    rv = init_xulrunner(xul_dir, app_dir)
    if rv != NS_OK:
        raise XPCOMError("init_xulrunner failed with code: %d" % rv)

def shutdown():
    shutdown_xulrunner()

class XPCOMError(Exception):
    pass

cdef void focusCallbackGlue(PRBool forward, void* data) with gil:
    cdef PyObject* retval
    retval = PyObject_CallMethod(<PyObject*>data,
            "on_browser_focus", "b", forward)
    if retval:
        Py_DECREF(retval)

cdef class XULRunnerBrowser:
    cdef MiroBrowserEmbed* browser

    def __init__(self, parent, x, y, width, height):
        self.browser = new_MiroBrowserEmbed()
        if not self.browser:
            raise XPCOMError("MiroBrowserEmbed Constructor failed")
        addref(self.browser)
        cdef nsresult rv
        rv = self.browser.init(parent, x, y, width, height)
        if rv != NS_OK:
            release(self.browser)
            raise XPCOMError("MiroBrowserEmbed.init() failed")

    def destroy(self):
        self.browser.destroy()

    def set_callback_object(self, handler):
        self.browser.SetFocusCallback(focusCallbackGlue, <void *>(handler))

    def _check_result(self, function, result):
        if result != NS_OK:
            raise XPCOMError("%s failed with code: %d" % (function, result))

    def resize(self, x, y, width, height):
        cdef nsresult rv
        rv = self.browser.resize(x, y, width, height)
        self._check_result('MiroBrowserEmbed.resize', rv)

    def load_uri(self, uri):
        cdef nsresult rv
        rv = self.browser.loadURI(uri)
        self._check_result('MiroBrowserEmbed.loadURI', rv)

    def focus(self):
        cdef nsresult rv
        rv = self.browser.focus()
        self._check_result('MiroBrowserEmbed.focus', rv)
