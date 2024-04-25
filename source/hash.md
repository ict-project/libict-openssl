# OpenSSL digest module wrapper

## Interface

### Hash value class `ict::hash::value`

Interface:
```c
    //! 
    //! @brief Returns the current hash.
    //! 
    //! @return The current hash.
    //! 
    ict::safe::string get() const;
    //! 
    //! @brief Returns the current hash.
    //! 
    //! @param output The current hash.
    //! 
    void get(ict::safe::string & output) const;
    //! 
    //! @brief Returns the hash type.
    //! 
    //! @return The hash type.
    //! 
    ict::hash::type_t getType() const;
    //! 
    //! @brief Data adding operator.
    //! 
    //! @param input Data to be digested.
    //! @return value& Reference to the current object.
    //! 
    value & operator()(const ict::safe::string & input);
    //! 
    //! @brief The hash assignment operator.
    //! 
    //! @param input The input object to assign.
    //! @return Reference to the current object.
    //! 
    value & operator=(const value & input);
    //! 
    //! @brief The hash comparison operator.
    //! 
    //! @param input The input object to compare.
    //! @return true The current hash is equal.
    //! @return false The current hash is not equal.
    //! 
    bool operator==(const value & input) const;
    //! 
    //! @brief The hash comparison operator.
    //! 
    //! @param input The input object to compare.
    //! @return true The current hash is not equal.
    //! @return false The current hash is equal.
    //! 
     bool operator!=(const value & input) const;
```

### Hash functions

```c
//! 
//! @brief Calculates the hash.
//! 
//! @param input Input.
//! @param hash_type The hash type.
//! @param output The computed hash.
//! @return Zero when no error.
//! 
int digest(const ict::safe::string & input,type_t hash_type,ict::safe::string & output);
//! 
//! @brief Calculates the hash.
//! 
//! @param input Input.
//! @param hash_type The hash type.
//! @return The computed hash.
//! 
inline ict::safe::string digest(const ict::safe::string & input,type_t hash_type);
```

## Available hashes

*Remark: It depends on OpenSSL version.* 

* `ict::hash::blake2b512`
* `ict::hash::blake2s256`
* `ict::hash::md5`
* `ict::hash::md5_sha1`
* `ict::hash::sha1`
* `ict::hash::sha224`
* `ict::hash::sha256`
* `ict::hash::sha3_224`
* `ict::hash::sha3_256`
* `ict::hash::sha3_384`
* `ict::hash::sha3_512`
* `ict::hash::sha384`
* `ict::hash::sha512`
* `ict::hash::sha512_224`
* `ict::hash::sha512_256`
* `ict::hash::shake128`
* `ict::hash::shake256`
* `ict::hash::sm3`
* `ict::hash::ssl3_md5`
* `ict::hash::ssl3_sha1`
