if BUILD_PYTHON
PYSUBDIR = wxPython
endif

SUBDIRS = src demo $(PYSUBDIR)

pkgconfdir = $(libdir)/pkgconfig
pkgconf_DATA = wxmozilla.pc

EXTRA_DIST = BUILD.Unix.txt BUILD.Win32.txt doxygen.config icons \
             wxmozilla.spec build

dist-hook:
	rm -rf `find $(distdir) -name 'CVS'`
