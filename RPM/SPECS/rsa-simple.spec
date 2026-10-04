Name:           rsa-simple
Version:        1.0
Release:        alt1
Summary:        Simple educational RSA encryption program
License:        Unknown
Group:          Other
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make

%description
Simple educational implementation of RSA encryption.
This version intentionally uses a simple and inefficient
modular exponentiation algorithm.

%prep
%setup -q -n rsa-simple-1.0

%build
%make_build

%install
make install DESTDIR=%buildroot PREFIX=%_prefix

%files
%_bindir/rsa-simple

%changelog
* Sun Oct 04 2026 User <user@localhost> 1.0-alt1
- Initial package