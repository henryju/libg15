Name: libg15
Summary: Library to handle the LCD and extra keys on the Logitech G15 Gaming Keyboard and similar devices
Version: 1.3.1
Release: 1%{?dist}
 
License: GPL
URL: https://github.com/henryju/libg15
Source0: https://github.com/henryju/libg15/archive/v.%{version}.tar.gz
 
BuildRequires: gcc, autoconf, automake, libtool, libusb-devel

%description
Library to handle the LCD and extra keys on the Logitech G15 Gaming Keyboard and similar devices    

%package        devel
Summary:        Headers and libraries for building apps that use libg15
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}

%description    devel
This package contains headers and libraries required to build applications that
use libg15.

%prep 
%autosetup

%build 
autoreconf -vi
%configure
make

%install 
rm -fr %{buildroot}
make install DESTDIR=%{buildroot}

%clean 
rm -fr %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files 
%defattr(-,root,root)
%doc AUTHORS COPYING INSTALL ChangeLog ChangeLog.old NEWS NEWS.old README.md
%{_libdir}/*.so.*

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}
%{_libdir}/*.a
%{_libdir}/*.la
%{_libdir}/*.so
%{_libdir}/pkgconfig/%{name}.pc
%{_datadir}/aclocal/*.m4

%changelog
