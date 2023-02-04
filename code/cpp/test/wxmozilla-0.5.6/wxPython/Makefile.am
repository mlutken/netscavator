
if BUILD_24

wxpythondir = $(WXPYTHONDIR)/wxPython
wxpython_PYTHON = contrib/mozilla/mozilla.py
# workaround a bug in automake by installing twice:
compatdir = $(WXPYTHONDIR)/wxPython
compat_PYTHON = contrib/mozilla/mozilla.py

wxpython_LTLIBRARIES = mozillac.la
mozillac_la_SOURCES = contrib/mozilla_wrap.cpp
mozillac_la_LDFLAGS = -avoid-version -module
mozillac_la_LIBADD = $(MOZILLA_LIBS) $(WX_LIBS) \
                     $(top_builddir)/src/lib@WXMOZILLALIB@.la
mozillac_la_CXXFLAGS = -DBUILD_24 \
					   $(MOZILLA_CFLAGS) $(WX_CXXFLAGS) \
                       -I$(top_srcdir)/src \
                       -I$(PYTHON_INCLUDE)

else

wxpythondir = $(WXPYTHONDIR)/wx
wxpython_PYTHON = contrib/mozilla25/wx/mozilla.py
compatdir = $(WXPYTHONDIR)/wxPython
compat_PYTHON = contrib/mozilla25/wxPython/mozilla.py

wxpython_LTLIBRARIES = _mozilla.la
_mozilla_la_SOURCES = contrib/mozilla_wrap.cpp
_mozilla_la_LDFLAGS = -avoid-version -module
_mozilla_la_LIBADD = $(MOZILLA_LIBS) $(WX_LIBS) \
                     $(top_builddir)/src/lib@WXMOZILLALIB@.la
_mozilla_la_CXXFLAGS = $(MOZILLA_CFLAGS) $(WX_CXXFLAGS) \
                       -I$(top_srcdir)/src \
                       -I$(PYTHON_INCLUDE) \
					   -DSWIG_TYPE_TABLE=_wxPython_table \
					   -DWXP_USE_THREAD=1

endif

EXTRA_DIST = setup.py README.txt demo contrib
