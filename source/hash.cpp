//! @file
//! @brief OpenSSL hash module - Source file.
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
//============================================
#include "local.h"
#include <stdexcept>
#include <set>
#include <openssl/md2.h>
#include <openssl/md4.h>
#include <openssl/md5.h>
#include <openssl/mdc2.h>
#include <openssl/ripemd.h>
#include <openssl/sha.h>
#include <openssl/whrlpool.h>
//============================================
namespace ict { namespace  hash { 
//============================================
#define MINEFIELD_SIZE 1000
class minefield{
private:
    char mf[MINEFIELD_SIZE];
    char getChar(std::size_t k){
        return((k+13)%0X100);
    }
public:
    minefield(){
        for(std::size_t k=0;k<MINEFIELD_SIZE;k++) mf[k]=getChar(k);
    }
    void test(){
        for(std::size_t k=0;k<MINEFIELD_SIZE;k++) {
            if (mf[k]!=getChar(k)){
                throw std::runtime_error("Boom! Your last step was "+std::to_string(k)+" ...");
            }
        }
    }
};

#define EVP_MD_TRANSLATE(type) case type: return(EVP_##type());
const EVP_MD * translate(type_t type){
    switch(type){
        #ifndef OPENSSL_NO_MD2
        EVP_MD_TRANSLATE(md2)
        #endif
        #ifndef OPENSSL_NO_MD4
        EVP_MD_TRANSLATE(md4)
        #endif
        #ifndef OPENSSL_NO_MD5
        EVP_MD_TRANSLATE(md5)
        EVP_MD_TRANSLATE(md5_sha1)
        #endif
        #ifndef OPENSSL_NO_BLAKE2
        EVP_MD_TRANSLATE(blake2b512)
        EVP_MD_TRANSLATE(blake2s256)
        #endif
        EVP_MD_TRANSLATE(sha1)
        EVP_MD_TRANSLATE(sha224)
        EVP_MD_TRANSLATE(sha256)
        EVP_MD_TRANSLATE(sha384)
        EVP_MD_TRANSLATE(sha512)
        EVP_MD_TRANSLATE(sha512_224)
        EVP_MD_TRANSLATE(sha512_256)
        EVP_MD_TRANSLATE(sha3_224)
        EVP_MD_TRANSLATE(sha3_256)
        EVP_MD_TRANSLATE(sha3_384)
        EVP_MD_TRANSLATE(sha3_512)
        EVP_MD_TRANSLATE(shake128)
        EVP_MD_TRANSLATE(shake256)
        #ifndef OPENSSL_NO_MDC2
        EVP_MD_TRANSLATE(mdc2)
        #endif
        #ifndef OPENSSL_NO_RMD160
        EVP_MD_TRANSLATE(ripemd160)
        #endif
        #ifndef OPENSSL_NO_WHIRLPOOL
        EVP_MD_TRANSLATE(whirlpool)
        #endif
        #ifndef OPENSSL_NO_SM3
        EVP_MD_TRANSLATE(sm3)
        #endif
        default: break;
    }
    return(nullptr);
}
#undef EVP_MD_TRANSLATE

template <typename Context,int Init(Context*),int Update(Context*,const void*,size_t),int Final(unsigned char *,Context*),size_t Length> class implementation: public interface{
private:
    const ict::hash::type_t t;
    Context context;
public:
    implementation(ict::hash::type_t t_):t(t_){
    }
    ~implementation(){
        ::memset(&context,std::rand()%0x100,sizeof(Context));
    }
    void init(){
        ::memset(&context,0x0,sizeof(Context));
        {
            int out=Init(&context);
            if (out!=1) throw std::runtime_error("Init failed!!!");
        }
    }
    void update(const ict::safe::string & input){
        int out=Update(&context,(const char *)input.c_str(),input.size());
        if (out!=1) throw std::runtime_error("Update failed!!!");
    }
    void final(ict::safe::string & output) const{
        unsigned char md[Length];
        Context ctx=context;
        int out=Final(md,&ctx);
        output.assign((char *)md,Length);
        ::memset(&md,std::rand()%0x100,Length);
        ::memset(&ctx,std::rand()%0x100,sizeof(Context));
        if (out!=1) throw std::runtime_error("Final failed!!!");
    }
    ict::hash::type_t type() const{
        return(t);
    }
    interface *clone() const{
        implementation * out=new implementation<Context,Init,Update,Final,Length>(t);
        if (out) out->context=context;
        return(out);
    }
};
#ifndef OPENSSL_NO_MDC2
inline int MDC2_Update(MDC2_CTX*c,const void* p,size_t s){
    return(::MDC2_Update(c,(const unsigned char*)p,s));
} 
#endif
interface *interface::factory(type_t type){
    switch(type){
        #ifndef OPENSSL_NO_MD2
        case type_t::md2:return(new implementation<MD2_CTX,MD2_Init,MD2_Update,MD2_Final,MD2_DIGEST_LENGTH>(type));
        #endif
        #ifndef OPENSSL_NO_MD4
        case type_t::md4:return(new implementation<MD4_CTX,MD4_Init,MD4_Update,MD4_Final,MD4_DIGEST_LENGTH>(type));
        #endif
        #ifndef OPENSSL_NO_MD5
        case type_t::md5:return(new implementation<MD5_CTX,MD5_Init,MD5_Update,MD5_Final,MD5_DIGEST_LENGTH>(type));
        //md5_sha1
        #endif
        #ifndef OPENSSL_NO_BLAKE2
        //blake2b512
        //blake2s256
        #endif
        case type_t::sha1:return(new implementation<SHA_CTX,SHA1_Init,SHA1_Update,SHA1_Final,SHA_DIGEST_LENGTH>(type));
        case type_t::sha224:return(new implementation<SHA256_CTX,SHA224_Init,SHA224_Update,SHA224_Final,SHA224_DIGEST_LENGTH>(type));
        case type_t::sha256:return(new implementation<SHA256_CTX,SHA256_Init,SHA256_Update,SHA256_Final,SHA256_DIGEST_LENGTH>(type));
        case type_t::sha384:return(new implementation<SHA512_CTX,SHA384_Init,SHA384_Update,SHA384_Final,SHA384_DIGEST_LENGTH>(type));
        case type_t::sha512:return(new implementation<SHA512_CTX,SHA512_Init,SHA512_Update,SHA512_Final,SHA512_DIGEST_LENGTH>(type));
        //sha512_224
        //sha512_256
        //sha3_224
        //sha3_256
        //sha3_384
        //sha3_512
        //shake128
        //shake256
        #ifndef OPENSSL_NO_MDC2
        case type_t::mdc2:return(new implementation<MDC2_CTX,MDC2_Init,MDC2_Update,MDC2_Final,MDC2_DIGEST_LENGTH>(type));
        #endif
        #ifndef OPENSSL_NO_RMD160
        case type_t::ripemd160:return(new implementation<RIPEMD160_CTX,RIPEMD160_Init,RIPEMD160_Update,RIPEMD160_Final,RIPEMD160_DIGEST_LENGTH>(type));
        #endif
        #ifndef OPENSSL_NO_WHIRLPOOL
        case type_t::whirlpool:return(new implementation<WHIRLPOOL_CTX,WHIRLPOOL_Init,WHIRLPOOL_Update,WHIRLPOOL_Final,WHIRLPOOL_DIGEST_LENGTH>(type));
        #endif
        #ifndef OPENSSL_NO_SM3
        //sm3
        #endif
        default:break;
    }
    return(nullptr);
}

value::value(type_t hash_type):iface(interface::factory(hash_type)){
    if (iface) iface->init();
}
value::value(const value & input):iface(input.iface->clone()){
}
value::~value(){
}
ict::safe::string value::get() const{
    ict::safe::string output;
    get(output);
    return(output);
}
void value::get(ict::safe::string & output) const{
    if (iface) {
        iface->final(output);
    } else {
        output.clear();
    }
}
ict::hash::type_t value::getType() const{
    if (iface) return(iface->type());
    return(type_t::error);
}
value & value::operator()(const ict::safe::string & input){
    if (iface) iface->update(input);
    return(*this);
}
value & value::operator=(const value & input){
    iface.reset(input.iface->clone());
    return(*this);
}
bool value::operator==(const value & input) const{
    return(get()==input.get());
}
bool value::operator!=(const value & input) const{
    return(get()!=input.get());
}

int digest(const ict::safe::string & input,type_t hash_type,ict::safe::string & output){
    value v(hash_type);
    v(input);
    v.get(output);
    return((v.getType()!=type_t::error)?0:1);
}

//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
#include <cstdlib>

int test_hash(ict::hash::type_t type){
    ict::safe::string input1("Ala ma kota.");
    ict::safe::string input2("Ala ma kota..");
    ict::safe::string input3("Ala ma kota!");
    ict::safe::string output1(ict::hash::digest(input1,type));
    ict::safe::string output2(ict::hash::digest(input2,type));
    ict::safe::string output3(ict::hash::digest(input3,type));
    if (!output1.size()) 
        return(1);
    if (!output2.size()) 
        return(2);
    if (!output3.size()) 
        return(3);
    if (output1==output2) 
        return(4);
    if (output2==output3) 
        return(5);
    if (output3==output1) 
        return(6);
    input1.resize(0x100+(std::rand()%(0x10)));
    input2.resize(0x100+(std::rand()%(0x10)));
    input3.resize(0x100+(std::rand()%(0x10)));
    for (auto &c:input1) c=std::rand()%0x80;
    for (auto &c:input2) c=std::rand()%0x80;
    for (auto &c:input3) c=std::rand()%0x80;
    {
        ict::hash::value v1(type);
        ict::hash::value v2(type);
        ict::hash::value v3(type);
        v1(input1);
        v2(input1+input2);
        v3=v2;
        v1(input2+input3);
        v2(input3);
        v3(input3);
        v1.get(output1);
        v2.get(output2);
        v3.get(output3);
        if (!output1.size()) 
            return(7);
        if (!output2.size()) 
            return(8);
        if (!output3.size()) 
            return(9);
        if (output1!=output2) 
            return(10);
        if (output2!=output3)
            return(11);
        if (output3!=output1) 
            return(12);
        if (v1!=v2) 
            return(13);
        if (v2!=v3)
            return(14);
        if (v3!=v1) 
            return(15);
    }
    return(0);
}

#define EVP_MD_TEST(type) \
REGISTER_TEST(hash,tc_##type){ \
    if (ict::hash::translate(ict::hash::type)){ \
        return(test_hash(ict::hash::type)); \
    } \
    return(0); \
}

EVP_MD_TEST(md2)
EVP_MD_TEST(md4)
EVP_MD_TEST(md5)
EVP_MD_TEST(sha1)
EVP_MD_TEST(sha224)
EVP_MD_TEST(sha256)
EVP_MD_TEST(sha384)
EVP_MD_TEST(sha512)
EVP_MD_TEST(ripemd160)
EVP_MD_TEST(whirlpool)

#endif
//===========================================