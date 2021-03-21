# OpenSSL cipher module wrapper

## Interface

### Wrapper for encryption keys `ict::cipher::password`
Interface:

```c
//!
//! @brief Constructs the encryption keys.
//!
//! @param input Password to be converted to encryption keys.
//! @param cipher_type The type of the cipher.
//! @param hash_type The type of hash to be used.
//! @param count The number of iterations of the hash function.
//!
password(const ict::safe::string & input,ict::cipher::type_t cipher_type,ict::hash::type_t hash_type=ict::hash::md5,int count=1);
//!
//! @brief Returns a pointer to the block encryption key.
//!
//! @return A pointer to the block encryption key.
//!
const unsigned char * getKey() const;
//!
//! @brief Returns a pointer to a vector that encrypts multiple consecutive blocks.
//!
//! @return A pointer to a vector that encrypts multiple consecutive blocks.
//!
const unsigned char * getIv() const;
//!
//! @brief Returns the size of the key to encrypt blocks.
//!
//! @return The size of the key to encrypt blocks.
//!
std::size_t getKeySize() const;
//!
//! @brief Returns the size of the encryption vector for multiple consecutive blocks.
//!
//! @return Size of the vector encoding multiple consecutive blocks.
//!
std::size_t getIvSize() const;
//!
//! @brief Checks that an object has been properly constructed.
//!
//! @return true Correct.
//! @return false An error has occurred.
//!
bool ok() const;
```

### Cipher functions

```c
//!
//! @brief An encrypting function.
//!
//! @param input Input for encryption.
//! @param pass Encryption keys.
//! @param output Encrypted output.
//! @param cipher_type Type of cipher.
//! @return Result 0 means success.
//!
int ict::cipher::encrypt(const ict::safe::string & input,const ict::cipher::password & pass,ict::safe::string & output,ict::cipher::type_t cipher_type);
//!
//! @brief A decryption function.
//!
//! @param input Input for decryption.
//! @param pass Encryption keys.
//! @param output Decrypted output.
//! @param cipher_type Type of cipher.
//! @return Result 0 means success.
//!
int ict::cipher::decrypt(const ict::safe::string & input,const ict::cipher::password & pass,ict::safe::string & output,ict::cipher::type_t cipher_type);
//!
//! @brief An encrypting function.
//!
//! @param input Input for encryption.
//! @param pass Encryption keys.
//! @param cipher_type Type of cipher.
//! @return Encrypted output.
//!
inline ict::safe::string ict::cipher::encrypt(const ict::safe::string & input,const ict::cipher::password & pass,ict::cipher::type_t cipher_type);
//!
//! @brief A decryption function.
//!
//! @param input Input for decryption.
//! @param pass Encryption keys.
//! @param cipher_type Type of cipher.
//! @return Decrypted output.
//! 
inline ict::safe::string ict::cipher::decrypt(const ict::safe::string & input,const ict::cipher::password & pass,ict::cipher::type_t cipher_type);
//!
//! @brief An encrypting function.
//!
//! @param input Input for encryption.
//! @param pass Password.
//! @param output Encrypted output.
//! @param cipher_type Type of cipher.
//! @return Result 0 means success.
//!
int ict::cipher::encrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::safe::string & output,ict::cipher::type_t cipher_type);
//!
//! @brief A decryption function.
//!
//! @param input Input for decryption.
//! @param pass Password.
//! @param output Decrypted output.
//! @param cipher_type Type of cipher.
//! @return Result 0 means success.
//!
int ict::cipher::decrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::safe::string & output,ict::cipher::type_t cipher_type);
//!
//! @brief An encrypting function.
//!
//! @param input Input for encryption.
//! @param pass Password.
//! @param cipher_type Type of cipher.
//! @return Encrypted output.
//! 
inline ict::safe::string ict::cipher::encrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::cipher::type_t cipher_type);
//!
//! @brief A decryption function.
//!
//! @param input Input for decryption.
//! @param pass Password.
//! @param cipher_type Type of cipher.
//! @return Decrypted output.
//! 
inline ict::safe::string ict::cipher::decrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::cipher::type_t cipher_type);
```

## Available ciphers

*Remark: It depends on OpenSSL version.* 

* `ict::cipher::des_ecb`
* `ict::cipher::des_ede`
* `ict::cipher::des_ede3`
* `ict::cipher::es_ede_ecb`
* `ict::cipher::des_ede3_ecb`
* `ict::cipher::des_cfb64`
* `ict::cipher::des_cfb1`
* `ict::cipher::des_cfb8`
* `ict::cipher::des_ede_cfb64`
* `ict::cipher::des_ede3_cfb64`
* `ict::cipher::des_ede3_cfb1`
* `ict::cipher::des_ede3_cfb8`
* `ict::cipher::des_ofb`
* `ict::cipher::des_ede_ofb`
* `ict::cipher::des_ede3_ofb`
* `ict::cipher::des_cbc`
* `ict::cipher::des_ede_cbc`
* `ict::cipher::des_ede3_cbc`
* `ict::cipher::desx_cbc`
* `ict::cipher::rc4`
* `ict::cipher::rc4_40`
* `ict::cipher::rc4_hmac_md5`
* `ict::cipher::rc2_ecb`
* `ict::cipher::rc2_cbc`
* `ict::cipher::rc2_40_cbc`
* `ict::cipher::rc2_64_cbc`
* `ict::cipher::rc2_cfb64`
* `ict::cipher::rc2_ofb`
* `ict::cipher::bf_ecb`
* `ict::cipher::bf_cbc`
* `ict::cipher::bf_cfb64`
* `ict::cipher::bf_ofb`
* `ict::cipher::cast5_ecb`
* `ict::cipher::cast5_cbc`
* `ict::cipher::cast5_cfb64`
* `ict::cipher::cast5_ofb`
* `ict::cipher::aes_128_ecb`
* `ict::cipher::aes_128_cbc`
* `ict::cipher::aes_128_cfb1`
* `ict::cipher::aes_128_cfb8`
* `ict::cipher::aes_128_cfb128`
* `ict::cipher::aes_128_ofb`
* `ict::cipher::aes_128_ctr`
* `ict::cipher::aes_128_xts`
* `ict::cipher::aes_192_ecb`
* `ict::cipher::aes_192_cbc`
* `ict::cipher::aes_192_cfb1`
* `ict::cipher::aes_192_cfb8`
* `ict::cipher::aes_192_cfb128`
* `ict::cipher::aes_192_ofb`
* `ict::cipher::aes_192_ctr`
* `ict::cipher::aes_256_ecb`
* `ict::cipher::aes_256_cbc`
* `ict::cipher::aes_256_cfb1`
* `ict::cipher::aes_256_cfb8`
* `ict::cipher::aes_256_cfb128`
* `ict::cipher::aes_256_ofb`
* `ict::cipher::aes_256_ctr`
* `ict::cipher::aes_256_xts`
* `ict::cipher::aes_128_cbc_hmac_sha1`
* `ict::cipher::aes_256_cbc_hmac_sha1`
* `ict::cipher::aes_128_cbc_hmac_sha256`
* `ict::cipher::aes_256_cbc_hmac_sha256`
* `ict::cipher::aria_128_ecb`
* `ict::cipher::aria_128_cbc`
* `ict::cipher::aria_128_cfb1`
* `ict::cipher::aria_128_cfb8`
* `ict::cipher::aria_128_cfb128`
* `ict::cipher::aria_128_ctr`
* `ict::cipher::aria_128_ofb`
* `ict::cipher::aria_192_ecb`
* `ict::cipher::aria_192_cbc`
* `ict::cipher::aria_192_cfb1`
* `ict::cipher::aria_192_cfb8`
* `ict::cipher::aria_192_cfb128`
* `ict::cipher::aria_192_ctr`
* `ict::cipher::aria_192_ofb`
* `ict::cipher::aria_256_ecb`
* `ict::cipher::aria_256_cbc`
* `ict::cipher::aria_256_cfb1`
* `ict::cipher::aria_256_cfb8`
* `ict::cipher::aria_256_cfb128`
* `ict::cipher::aria_256_ctr`
* `ict::cipher::aria_256_ofb`
* `ict::cipher::camellia_128_ecb`
* `ict::cipher::camellia_128_cbc`
* `ict::cipher::camellia_128_cfb1`
* `ict::cipher::camellia_128_cfb8`
* `ict::cipher::camellia_128_cfb128`
* `ict::cipher::camellia_128_ofb`
* `ict::cipher::camellia_128_ctr`
* `ict::cipher::camellia_192_ecb`
* `ict::cipher::camellia_192_cbc`
* `ict::cipher::camellia_192_cfb1`
* `ict::cipher::camellia_192_cfb8`
* `ict::cipher::camellia_192_cfb128`
* `ict::cipher::camellia_192_ofb`
* `ict::cipher::camellia_192_ctr`
* `ict::cipher::camellia_256_ecb`
* `ict::cipher::camellia_256_cbc`
* `ict::cipher::camellia_256_cfb1`
* `ict::cipher::camellia_256_cfb8`
* `ict::cipher::camellia_256_cfb128`
* `ict::cipher::camellia_256_ofb`
* `ict::cipher::camellia_256_ctr`
* `ict::cipher::chacha20`
* `ict::cipher::chacha20_poly1305`
* `ict::cipher::seed_ecb`
* `ict::cipher::seed_cbc`
* `ict::cipher::seed_cfb128`
* `ict::cipher::seed_ofb`
* `ict::cipher::sm4_ecb`
* `ict::cipher::sm4_cbc`
* `ict::cipher::sm4_cfb128`
* `ict::cipher::sm4_ofb`
* `ict::cipher::sm4_ctr`