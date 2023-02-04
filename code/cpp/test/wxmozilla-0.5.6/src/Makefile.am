
AM_CXXFLAGS = $(MOZILLA_CFLAGS) $(WX_CXXFLAGS) $(GTK_CFLAGS) -fno-rtti

lib_LTLIBRARIES = lib@WXMOZILLALIB@.la

# NB: These are headers that will be *installed*. Internal headers should go
#     into _SOURCES variable.
WXMOZILLAHEADERS = \
        wxMozilla.h \
        wxMozillaBrowser.h \
        wxMozillaBrowserChrome.h \
        wxMozillaWindow.h \
        wxMozillaEvents.h \
	wxMozillaComponents.h \
	wxMozillaProtocolHandler.h \
		wxMozillaSettings.h

lib@WXMOZILLALIB@_la_SOURCES = \
        wxMozillaBrowser.cpp \
        wxMozillaBrowserChrome.cpp \
        wxMozillaWindow.cpp \
        wxMozillaEvents.cpp \
		wxMozillaSettings.cpp \
		helpers.cpp \
		helpers.h \
		wxMozillaBrowserInterface.h \
		cstmdlg.h \
		cstmdlg.cpp \
		wxMozillaDialogs.h \
		wxMozillaProtocolHandler.cpp \
		wxMozillaDialogs.cpp

lib@WXMOZILLALIB@_la_LDFLAGS = -version-info 0:0:0 
lib@WXMOZILLALIB@_la_LIBADD = $(MOZILLA_LIBS) $(WX_LIBS)

wxmozillaincludedir=$(includedir)/wxmozilla
wxmozillainclude_HEADERS=$(WXMOZILLAHEADERS)

EXTRA_DIST = compat makelib.vc wxMozilla.mak
