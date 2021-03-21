# OpenSSL C++ wrapper [![Build Status](https://travis-ci.org/ict-project/libict-openssl.svg?branch=main)](https://travis-ci.org/ict-project/libict-openssl)

This code implements a simple OpenSSL C++ wrapper.

See:
* [hash](source/hash.md) for more details about hash functions;
* [cipher](source/cipher.md) for more details about cipher functions.

Releases:
* Branch release-v1 [![Build Status](https://travis-ci.org/ict-project/libict-openssl.svg?branch=release-v1)](https://travis-ci.org/ict-project/libict-openssl)

## Building instructions

```sh
make # Build library
make test # Execute all tests
make package # Create library package
make package_source  # Create source package
```