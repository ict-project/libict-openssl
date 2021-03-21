//! @file
//! @brief OpenSSL cipher module - header file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @version 1.0
//! @date 2012-2021
//! @copyright ICT-Project Mariusz Ornowski (ict-project.pl)
/* **************************************************************
Copyright (c) 2012-2021, ICT-Project Mariusz Ornowski (ict-project.pl)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the ICT-Project Mariusz Ornowski nor the names
of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************/
#ifndef _OPENSSL_CIPHER_HEADER
#define _OPENSSL_CIPHER_HEADER
//============================================
#include "string.hpp"
#include "hash.hpp"
//============================================
namespace ict { namespace  cipher {
//============================================
//! Typy szyfratorów.
enum type_t {
    des_ecb,
    des_ede,
    des_ede3,
    des_ede_ecb,
    des_ede3_ecb,
    des_cfb64,
    des_cfb1,
    des_cfb8,
    des_ede_cfb64,
    des_ede3_cfb64,
    des_ede3_cfb1,
    des_ede3_cfb8,
    des_ofb,
    des_ede_ofb,
    des_ede3_ofb,
    des_cbc,
    des_ede_cbc,
    des_ede3_cbc,
    desx_cbc,
    des_ede3_wrap,
    rc4,
    rc4_40,
    rc4_hmac_md5,
    idea_ecb,
    idea_cfb64,
    idea_ofb,
    idea_cbc,
    rc2_ecb,
    rc2_cbc,
    rc2_40_cbc,
    rc2_64_cbc,
    rc2_cfb64,
    rc2_ofb,
    bf_ecb,
    bf_cbc,
    bf_cfb64,
    bf_ofb,
    cast5_ecb,
    cast5_cbc,
    cast5_cfb64,
    cast5_ofb,
    rc5_32_12_16_cbc,
    rc5_32_12_16_ecb,
    rc5_32_12_16_cfb64,
    rc5_32_12_16_ofb,
    aes_128_ecb,
    aes_128_cbc,
    aes_128_cfb1,
    aes_128_cfb8,
    aes_128_cfb128,
    aes_128_ofb,
    aes_128_ctr,
    aes_128_ccm,
    aes_128_gcm,
    aes_128_xts,
    aes_128_wrap,
    aes_128_wrap_pad,
    aes_128_ocb,
    aes_192_ecb,
    aes_192_cbc,
    aes_192_cfb1,
    aes_192_cfb8,
    aes_192_cfb128,
    aes_192_ofb,
    aes_192_ctr,
    aes_192_ccm,
    aes_192_gcm,
    aes_192_wrap,
    aes_192_wrap_pad,
    aes_192_ocb,
    aes_256_ecb,
    aes_256_cbc,
    aes_256_cfb1,
    aes_256_cfb8,
    aes_256_cfb128,
    aes_256_ofb,
    aes_256_ctr,
    aes_256_ccm,
    aes_256_gcm,
    aes_256_xts,
    aes_256_wrap,
    aes_256_wrap_pad,
    aes_256_ocb,
    aes_128_cbc_hmac_sha1,
    aes_256_cbc_hmac_sha1,
    aes_128_cbc_hmac_sha256,
    aes_256_cbc_hmac_sha256,
    aria_128_ecb,
    aria_128_cbc,
    aria_128_cfb1,
    aria_128_cfb8,
    aria_128_cfb128,
    aria_128_ctr,
    aria_128_ofb,
    aria_128_gcm,
    aria_128_ccm,
    aria_192_ecb,
    aria_192_cbc,
    aria_192_cfb1,
    aria_192_cfb8,
    aria_192_cfb128,
    aria_192_ctr,
    aria_192_ofb,
    aria_192_gcm,
    aria_192_ccm,
    aria_256_ecb,
    aria_256_cbc,
    aria_256_cfb1,
    aria_256_cfb8,
    aria_256_cfb128,
    aria_256_ctr,
    aria_256_ofb,
    aria_256_gcm,
    aria_256_ccm,
    camellia_128_ecb,
    camellia_128_cbc,
    camellia_128_cfb1,
    camellia_128_cfb8,
    camellia_128_cfb128,
    camellia_128_ofb,
    camellia_128_ctr,
    camellia_192_ecb,
    camellia_192_cbc,
    camellia_192_cfb1,
    camellia_192_cfb8,
    camellia_192_cfb128,
    camellia_192_ofb,
    camellia_192_ctr,
    camellia_256_ecb,
    camellia_256_cbc,
    camellia_256_cfb1,
    camellia_256_cfb8,
    camellia_256_cfb128,
    camellia_256_ofb,
    camellia_256_ctr,
    chacha20,
    chacha20_poly1305,
    seed_ecb,
    seed_cbc,
    seed_cfb128,
    seed_ofb,
    sm4_ecb,
    sm4_cbc,
    sm4_cfb128,
    sm4_ofb,
    sm4_ctr,
};

//! Zamienia hasło na klucze szyfrujące.
class password {
private:
    //! Klucz do szyfrowania bloków.
    ict::safe::string key;
    //! Wektor szyfrujący wiele kolejnych bloków.
    ict::safe::string iv;
public:
    //! 
    //! @brief Konstruuje klucze szyfrujące.
    //! 
    //! @param input Hasło do zamiany na klucze szyfrujące.
    //! @param cipher_type Typ szyfratora.
    //! @param hash_type Typ skrótu, który zostanie wykorzystany.
    //! @param count Liczba iteracji funkcji skrótu.
    //! 
    password(const ict::safe::string & input,ict::cipher::type_t cipher_type,ict::hash::type_t hash_type=ict::hash::type_t::md5,int count=1);
    //! 
    //! @brief Zwraca wskaźnik do klucza do szyfrowania bloków.
    //! 
    //! @return Wskaźnik do klucza do szyfrowania bloków.
    //! 
    const unsigned char* getKey() const {return((const unsigned char*)key.c_str());}
    //! 
    //! @brief Zwraca wskaźnik do wektora szyfrującego wiele kolejnych bloków.
    //! 
    //! @return Wskaźnik do wektora szyfrującego wiele kolejnych bloków.
    //! 
    const unsigned char* getIv() const {return((const unsigned char*)iv.c_str());}
    //! 
    //! @brief Zwraca rozmiar klucza do szyfrowania bloków.
    //! 
    //! @return Rozmiar klucza do szyfrowania bloków.
    //! 
    std::size_t getKeySize() const {return(key.size());}
    //! 
    //! @brief Zwraca rozmiar wektora szyfrującego wiele kolejnych bloków.
    //! 
    //! @return Rozmiar wektora szyfrującego wiele kolejnych bloków.
    //! 
    std::size_t getIvSize() const {return(iv.size());}
    //! 
    //! @brief Sprawdza, czy obiekt został poprawnie skonstruowany.
    //! 
    //! @return true Poprawnie.
    //! @return false Wystąpił błąd.
    //! 
    bool ok() const {return(key.size()&&iv.size());}
};

//! 
//! @brief Funkcja szyfrująca.
//! 
//! @param input Wejście do zaszyfrowania.
//! @param pass Klucze szyfrujące.
//! @param output Zaszyfrowane wyjście.
//! @param cipher_type Wybór szyfratora.
//! @return Wynik 0 oznacza sukces.
//! 
int encrypt(const ict::safe::string & input,const password & pass,ict::safe::string & output,type_t cipher_type);
//! 
//! @brief Funkcja deszyfrująca.
//! 
//! @param input Wejście do odszyfrowania.
//! @param pass Klucze szyfrujące.
//! @param output Odszyfrowane wyjście.
//! @param cipher_type Wybór szyfratora.
//! @return Wynik 0 oznacza sukces. 
//! 
int decrypt(const ict::safe::string & input,const password & pass,ict::safe::string & output,type_t cipher_type);
//! 
//! @brief Funkcja szyfrująca.
//! 
//! @param input Wejście do zaszyfrowania.
//! @param pass Klucze szyfrujące.
//! @param cipher_type Wybór szyfratora.
//! @return Zaszyfrowane wyjście.
//! 
inline ict::safe::string encrypt(const ict::safe::string & input,const password & pass,type_t cipher_type){
    ict::safe::string output;
    encrypt(input,pass,output,cipher_type);
    return(output);
}
//! 
//! @brief Funkcja deszyfrująca.
//! 
//! @param input Wejście do odszyfrowania.
//! @param pass Klucze szyfrujące.
//! @param cipher_type Wybór szyfratora.
//! @return Odszyfrowane wyjście. 
//! 
inline ict::safe::string decrypt(const ict::safe::string & input,const password & pass,type_t cipher_type){
    ict::safe::string output;
    decrypt(input,pass,output,cipher_type);
    return(output);
}
//! 
//! @brief Funkcja szyfrująca.
//! 
//! @param input Wejście do zaszyfrowania.
//! @param pass Hasło.
//! @param output Zaszyfrowane wyjście.
//! @param cipher_type Wybór szyfratora.
//! @return Wynik 0 oznacza sukces.
//!
int encrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::safe::string & output,type_t cipher_type);
//! 
//! @brief Funkcja deszyfrująca.
//! 
//! @param input Wejście do odszyfrowania.
//! @param pass Hasło.
//! @param output Odszyfrowane wyjście.
//! @param cipher_type Wybór szyfratora.
//! @return Wynik 0 oznacza sukces. 
//! 
int decrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::safe::string & output,type_t cipher_type);
//! 
//! @brief Funkcja szyfrująca.
//! 
//! @param input Wejście do zaszyfrowania.
//! @param pass Hasło.
//! @param cipher_type Wybór szyfratora.
//! @return Zaszyfrowane wyjście.
//! 
inline ict::safe::string encrypt(const ict::safe::string & input,const ict::safe::string & pass,type_t cipher_type){
    ict::safe::string output;
    encrypt(input,pass,output,cipher_type);
    return(output);
}
//! 
//! @brief Funkcja deszyfrująca.
//! 
//! @param input Wejście do odszyfrowania.
//! @param pass Hasło.
//! @param cipher_type Wybór szyfratora.
//! @return Odszyfrowane wyjście. 
//! 
inline ict::safe::string decrypt(const ict::safe::string & input,const ict::safe::string & pass,type_t cipher_type){
    ict::safe::string output;
    decrypt(input,pass,output,cipher_type);
    return(output);
}
//============================================
} }
//============================================
#endif