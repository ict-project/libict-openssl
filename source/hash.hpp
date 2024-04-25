//! @file
//! @brief OpenSSL hash module - header file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//!
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
#ifndef _OPENSSL_HASH_HEADER
#define _OPENSSL_HASH_HEADER
//============================================
#include "string.hpp"
//============================================
namespace ict { namespace  hash { 
//===========================================
//! Typy hash'y.
enum type_t {
    blake2b512,
    blake2s256,
    md4,
    md5,
    md5_sha1,
    ripemd,
    ripemd160,
    rmd160,
    sha1,
    sha224,
    sha256,
    sha3_224,
    sha3_256,
    sha3_384,
    sha3_512,
    sha384,
    sha512,
    sha512_224,
    sha512_256,
    shake128,
    shake256,
    sm3,
    ssl3_md5,
    ssl3_sha1,
    whirlpool,
    error
};

//! Interfejs do algorytmu hash'a.
class interface{
public:
    //! 
    //! @brief Destruktor
    //! 
    virtual ~interface(){}
    //! 
    //! @brief Inicjuje algorytm.
    //! 
    virtual void init()=0;
    //! 
    //! @brief Dodanie danych do algorytmu.
    //! 
    //! @param input Dane do przeliczenia.
    //! 
    virtual void update(const ict::safe::string & input)=0;
    //! 
    //! @brief Zwraca aktualny hash.
    //! 
    //! @param output Aktualny hash.
    //! 
    virtual void final(ict::safe::string & output) const=0;
    //! 
    //! @brief Zwraca typ hash'a.
    //! 
    //! @return ict::hash::type_t Typ hash'a. 
    //! 
    virtual ict::hash::type_t type() const=0;
    //! 
    //! @brief Zwraca dokładną kopię hash'a.
    //! 
    //! @return interface* Wskaźnik do kopi hash'a.
    //! 
    virtual interface *clone() const=0;
    //! 
    //! @brief Zwraca nowy hash.
    //! 
    //! @param type Typ hash'a do uwtorzenia.
    //! @return interface* Wskaźnik do hash'a.
    //! 
    static interface *factory(type_t type); 
};

//! Klasa reprezentująca hash'a.
class value{
private:
    //! Wskaźnik do interfejsu.
    std::unique_ptr<interface> iface;
public:
    //! 
    //! @brief Konstruktor hash'a.
    //! 
    //! @param hash_type Typ hash'a, który ma być utworzony.
    //! 
    value(type_t hash_type);
    //! 
    //! @brief Konstruktor kopiujący hash'a.
    //! 
    //! @param input Kopiowany hash.
    //! 
    value(const value & input);
    //! 
    //! @brief Destruktor.
    //! 
    ~value();
    //! 
    //! @brief Zwraca aktualny hash.
    //! 
    //! @return Aktualny hash.
    //! 
    ict::safe::string get() const;
    //! 
    //! @brief Zwraca aktualny hash.
    //! 
    //! @param output Aktualny hash.
    //! 
    void get(ict::safe::string & output) const;
    //! 
    //! @brief Zwraca typ hash'a.
    //! 
    //! @return Typ hash'a.
    //! 
    ict::hash::type_t getType() const;
    //! 
    //! @brief Operator dodania danych.
    //! 
    //! @param input Dane do przeliczenia.
    //! @return value& Referencja do aktualnego hash'a.
    //! 
    value & operator()(const ict::safe::string & input);
    //! 
    //! @brief Operator przypisania hash'a.
    //! 
    //! @param input Obiekt wejściowy do przypisania.
    //! @return Referencja do aktualnego hash'a.
    //! 
    value & operator=(const value & input);
    //! 
    //! @brief Operator porówniania hash'a.
    //! 
    //! @param input Obiekt wejściowy do porównania.
    //! @return true Aktualny hash równy.
    //! @return false  Aktualny hash różny.
    //! 
    bool operator==(const value & input) const;
    //! 
    //! @brief Operator porówniania hash'a.
    //! 
    //! @param input Obiekt wejściowy do porównania.
    //! @return true Aktualny hash różny.
    //! @return false Aktualny hash równy.
    //! 
     bool operator!=(const value & input) const;
};

//! 
//! @brief Oblicza hash.
//! 
//! @param input Dane wejściowe.
//! @param hash_type Typ hash'a.
//! @param output Obliczony hash.
//! @return Zero, gdy brak błędu.
//! 
int digest(const ict::safe::string & input,type_t hash_type,ict::safe::string & output);
//! 
//! @brief Oblicza hash.
//! 
//! @param input Dane wejściowe.
//! @param hash_type Typ hash'a.
//! @return Obliczony hash.
//! 
inline ict::safe::string digest(const ict::safe::string & input,type_t hash_type){
    ict::safe::string output;
    digest(input,hash_type,output);
    return(output);
}
//===========================================
} }
//============================================
#endif