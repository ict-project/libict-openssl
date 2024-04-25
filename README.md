# OpenSSL C++ wrapper

This code implements a simple OpenSSL C++ wrapper.

See:
* [hash](source/hash.md) for more details about hash functions;
* [cipher](source/cipher.md) for more details about cipher functions.

Releases:
* Branch release-v1 

## Building instructions

```sh
make # Build library
make test # Execute all tests
make package # Create library package
make package_source  # Create source package
```