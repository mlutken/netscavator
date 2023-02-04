AM_CXXFLAGS = $(MOZILLA_CFLAGS) $(WX_CXXFLAGS) \
              -I$(top_srcdir)/src -fno-rtti

noinst_PROGRAMS = wxMozillaDemo wxMozillaProtocolsDemo


wxMozillaDemo_SOURCES = main.cpp

wxMozillaDemo_LDADD = $(MOZILLA_LIBS) $(WX_LIBS) \
                      $(top_builddir)/src/lib@WXMOZILLALIB@.la

wxMozillaProtocolsDemo_SOURCES = protocols.cpp
wxMozillaProtocolsDemo_LDADD = $(MOZILLA_LIBS) $(WX_LIBS) \
                      $(top_builddir)/src/lib@WXMOZILLALIB@.la

EXTRA_DIST = makeprog.vc
