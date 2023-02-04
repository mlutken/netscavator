%define build_python    1
%define build_gre       0
%{?_with_python: %{expand: %%define build_python 1}}
%{?_without_python: %{expand: %%define build_python 0}}
%{?_with_gre: %{expand: %%define build_gre 1}}
%{?_without_gre: %{expand: %%define build_gre 0}}

%{expand:%%define mozilla_version %(rpm -q --queryformat='%{VERSION}' mozilla)}

%define mozilladir    %{_libdir}/mozilla-%{mozilla_version}
%define wxpythondir   %{_libdir}/wxPython
%define wxmozilladir  %{_libdir}/wxmozilla-%{version}
%define gredir        %{wxmozilladir}/gre

Name:          wxmozilla
Version:       0.5.6
%if %build_gre
Release:       1all
%else
Release:       1
%endif
Source0:        %{name}-%{version}.tar.gz
%if %build_gre
Source1:       mozilla-source-1.3.tar.bz2
%endif

Prefix:        /usr
Summary:       wxWindows interface to Mozilla
License:       wxWindows Licence
Group:         Development/Libraries
URL:           http://wxmozilla.sourceforge.net
Packager:      Vaclav Slavik <vaclav.slavik@matfyz.cz>
BuildRoot:     /var/tmp/%{name}-%{version}-root

BuildRequires: doxygen
BuildRequires: wxGTK-devel >= 2.4.0
%if !%build_gre
BuildRequires: mozilla-devel >= 1.3
%endif
%if %build_python
BuildRequires: wxPythonGTK-devel
%endif

Requires:      wxGTK >= 2.4.0
%if !%build_gre
Requires:      mozilla = %{mozilla_version}
%endif

%description
wxWindows interface to Mozilla's Gecko HTML renderer.

%package devel
Summary:       wxMozilla development files
Group:         Development/Libraries
Requires:      wxmozilla = %{version}
Requires:      pkgconfig
Requires:      wxGTK-devel >= 2.4.0

%description devel
Header files for wxMozilla.

%if %build_gre
%define python_dependency wxmozilla = %{version}
%else
%define python_dependency mozilla = %{mozilla_version}
%endif

%if %build_python
%package python
Summary:       wxPython binding for wxMozilla
Group:         Development/Python
Requires:      wxPythonGTK >= 2.4.0
Requires:      %{python_dependency}

%description python
wxPython binding for wxMozilla.
%endif

%prep
%if %build_gre
%setup -q -a 1
%else
%setup -q
%endif

%build

%if %build_gre
MOZINST=`pwd`/mozilla/INST
(
cd mozilla
mkdir -p BUILD
mkdir -p INST
cd BUILD
../configure --prefix=%{wxmozilladir} \
             --enable-optimize --disable-debug --enable-strip \
             --with-default-mozilla-five-home=%{gredir} \
             --with-user-appdir=.wxmozilla \
             --enable-xft --disable-freetype2 \
             --disable-installer --disable-mailnews
make
(cd embedding/config ; make)
make install prefix=$MOZINST
)
%endif

%if %build_gre
GRE_CONFIGURE_FLAGS="--with-mozilla-includes=$MOZINST/include/mozilla-1.3 \
                     --with-mozilla-libs=$MOZINST/lib/mozilla-1.3 \
                     --with-mozilla-home=%{gredir}"
%endif

%if %build_python
mkdir -p PYTHON
(cd PYTHON
../configure --prefix=/usr/lib/wxPython --enable-python \
             --with-wx-config=/usr/lib/wxPython/bin/wx-config \
             $GRE_CONFIGURE_FLAGS
make pythondir='/usr/lib/python$(PYTHON_VERSION)/site-packages')
%endif

%configure $GRE_CONFIGURE_FLAGS
%if %build_gre
mv wxmozilla.pc wxmozilla.pc.broken
cat wxmozilla.pc.broken | \
  sed -e "s@$MOZINST@%{wxmozilladir}@g" | \
  sed -e "s@%{wxmozilladir}/lib/mozilla-1.3@%{gredir}@g" >wxmozilla.pc
%endif
make

mkdir -p doc/html
doxygen doxygen.config

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT
%if %build_gre
mkdir -p $RPM_BUILD_ROOT%{gredir}
(cd mozilla/BUILD/dist/Embed ; cp -Rf * $RPM_BUILD_ROOT%{gredir})
%endif
%makeinstall
%if %build_python
(cd PYTHON
make install DESTDIR=$RPM_BUILD_ROOT \
             pythondir='/usr/lib/python$(PYTHON_VERSION)/site-packages')
%endif
%if %build_gre
(cd mozilla/BUILD
make install DESTDIR=$RPM_BUILD_ROOT)
%endif

%clean
rm -rf $RPM_BUILD_ROOT


%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%defattr(-,root,root)
%doc NEWS README AUTHORS COPYING ChangeLog 
%{_libdir}/libwxmozilla*.so.*
%if %build_gre
%dir %{wxmozilladir}
%dir %{gredir}
%{gredir}/*
%endif

%files devel
%defattr(-,root,root)
%doc doc/html/*
%dir %{_includedir}/wxmozilla
%dir %{_includedir}/wxmozilla/*
%{_libdir}/lib*.so
%{_libdir}/lib*.a
%{_libdir}/lib*.la
%{_libdir}/pkgconfig/wxmozilla.pc

%if %build_python
%files python
%defattr(-,root,root)
%dir %{wxpythondir}/lib/libwxmozilla*.so.*
%dir %{_libdir}/python*/site-packages/wxPython/*.py*
%dir %{_libdir}/python*/site-packages/wxPython/*.so
%endif
