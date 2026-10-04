Name:           rsa-optimized
Version:        1.0
Release:        alt1
Summary:        Optimized educational RSA encryption program
License:        Unknown
Group:          Other
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make

%description
Optimized educational implementation of RSA encryption.
This version uses binary modular exponentiation.

%prep
%setup -q -n rsa-optimized-1.0

%build
%make_build

%install
make install DESTDIR=%buildroot PREFIX=%_prefix

%files
%_bindir/rsa-optimized

%changelog
* Sun Oct 04 2026 User <user@localhost> 1.0-alt1
- Initial package