//! @file
//! @brief OpenSSL cipher module - Source file.
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
//============================================
namespace ict { namespace  cipher {
//============================================
using EVP_CIPHER_CTX_free_ptr=std::unique_ptr<EVP_CIPHER_CTX,decltype(&::EVP_CIPHER_CTX_free)>;

#define ICT_OPENSSL_NO_WRAP
#define ICT_OPENSSL_NO_CCM
#define ICT_OPENSSL_NO_GCM
#define ICT_OPENSSL_NO_XTS

#define OPENSSL_NO_DES
#define OPENSSL_NO_RC4
#define OPENSSL_NO_RC2
#define OPENSSL_NO_BF
#define OPENSSL_NO_CAST
#define OPENSSL_NO_SEED
#define OPENSSL_NO_AES_CBC_HMAC

#ifndef OPENSSL_NO_OCB
#define OPENSSL_NO_OCB
#endif

#define EVP_CIPHER_TRANSLATE(type) case type: return(EVP_##type());
const EVP_CIPHER * translate(type_t type){
    switch(type){
        #ifndef OPENSSL_NO_DES
        EVP_CIPHER_TRANSLATE(des_ecb)
        EVP_CIPHER_TRANSLATE(des_ede)
        EVP_CIPHER_TRANSLATE(des_ede3)
        EVP_CIPHER_TRANSLATE(des_ede_ecb)
        EVP_CIPHER_TRANSLATE(des_ede3_ecb)
        EVP_CIPHER_TRANSLATE(des_cfb64)
        EVP_CIPHER_TRANSLATE(des_cfb1)
        EVP_CIPHER_TRANSLATE(des_cfb8)
        EVP_CIPHER_TRANSLATE(des_ede_cfb64)
        EVP_CIPHER_TRANSLATE(des_ede3_cfb64)
        EVP_CIPHER_TRANSLATE(des_ede3_cfb1)
        EVP_CIPHER_TRANSLATE(des_ede3_cfb8)
        EVP_CIPHER_TRANSLATE(des_ofb)
        EVP_CIPHER_TRANSLATE(des_ede_ofb)
        EVP_CIPHER_TRANSLATE(des_ede3_ofb)
        EVP_CIPHER_TRANSLATE(des_cbc)
        EVP_CIPHER_TRANSLATE(des_ede_cbc)
        EVP_CIPHER_TRANSLATE(des_ede3_cbc)
        EVP_CIPHER_TRANSLATE(desx_cbc)
        #ifndef ICT_OPENSSL_NO_WRAP
        EVP_CIPHER_TRANSLATE(des_ede3_wrap)
        #endif
        #endif
        #ifndef OPENSSL_NO_RC4
        EVP_CIPHER_TRANSLATE(rc4)
        EVP_CIPHER_TRANSLATE(rc4_40)
        #ifndef OPENSSL_NO_MD5
        EVP_CIPHER_TRANSLATE(rc4_hmac_md5)
        #endif
        #endif
        #ifndef OPENSSL_NO_IDEA
        EVP_CIPHER_TRANSLATE(idea_ecb)
        EVP_CIPHER_TRANSLATE(idea_cfb64)
        EVP_CIPHER_TRANSLATE(idea_ofb)
        EVP_CIPHER_TRANSLATE(idea_cbc)
        #endif
        #ifndef OPENSSL_NO_RC2
        EVP_CIPHER_TRANSLATE(rc2_ecb)
        EVP_CIPHER_TRANSLATE(rc2_cbc)
        EVP_CIPHER_TRANSLATE(rc2_40_cbc)
        EVP_CIPHER_TRANSLATE(rc2_64_cbc)
        EVP_CIPHER_TRANSLATE(rc2_cfb64)
        EVP_CIPHER_TRANSLATE(rc2_ofb)
        #endif
        #ifndef OPENSSL_NO_BF
        EVP_CIPHER_TRANSLATE(bf_ecb)
        EVP_CIPHER_TRANSLATE(bf_cbc)
        EVP_CIPHER_TRANSLATE(bf_cfb64)
        EVP_CIPHER_TRANSLATE(bf_ofb)
        #endif
        #ifndef OPENSSL_NO_CAST
        EVP_CIPHER_TRANSLATE(cast5_ecb)
        EVP_CIPHER_TRANSLATE(cast5_cbc)
        EVP_CIPHER_TRANSLATE(cast5_cfb64)
        EVP_CIPHER_TRANSLATE(cast5_ofb)
        #endif
        #ifndef OPENSSL_NO_RC5
        EVP_CIPHER_TRANSLATE(rc5_32_12_16_cbc)
        EVP_CIPHER_TRANSLATE(rc5_32_12_16_ecb)
        EVP_CIPHER_TRANSLATE(rc5_32_12_16_cfb64)
        EVP_CIPHER_TRANSLATE(rc5_32_12_16_ofb)
        #endif
        EVP_CIPHER_TRANSLATE(aes_128_ecb)
        EVP_CIPHER_TRANSLATE(aes_128_cbc)
        EVP_CIPHER_TRANSLATE(aes_128_cfb1)
        EVP_CIPHER_TRANSLATE(aes_128_cfb8)
        EVP_CIPHER_TRANSLATE(aes_128_cfb128)
        EVP_CIPHER_TRANSLATE(aes_128_ofb)
        EVP_CIPHER_TRANSLATE(aes_128_ctr)
        #ifndef ICT_OPENSSL_NO_CCM
        EVP_CIPHER_TRANSLATE(aes_128_ccm)
        #endif
        #ifndef ICT_OPENSSL_NO_GCM
        EVP_CIPHER_TRANSLATE(aes_128_gcm)
        #endif
        #ifndef ICT_OPENSSL_NO_XTS
        EVP_CIPHER_TRANSLATE(aes_128_xts)
        #endif
        #ifndef ICT_OPENSSL_NO_WRAP
        EVP_CIPHER_TRANSLATE(aes_128_wrap)
        EVP_CIPHER_TRANSLATE(aes_128_wrap_pad)
        #endif
        #ifndef OPENSSL_NO_OCB
        EVP_CIPHER_TRANSLATE(aes_128_ocb)
        #endif
        EVP_CIPHER_TRANSLATE(aes_192_ecb)
        EVP_CIPHER_TRANSLATE(aes_192_cbc)
        EVP_CIPHER_TRANSLATE(aes_192_cfb1)
        EVP_CIPHER_TRANSLATE(aes_192_cfb8)
        EVP_CIPHER_TRANSLATE(aes_192_cfb128)
        EVP_CIPHER_TRANSLATE(aes_192_ofb)
        EVP_CIPHER_TRANSLATE(aes_192_ctr)
        #ifndef ICT_OPENSSL_NO_CCM
        EVP_CIPHER_TRANSLATE(aes_192_ccm)
        #endif
        #ifndef ICT_OPENSSL_NO_GCM
        EVP_CIPHER_TRANSLATE(aes_192_gcm)
        #endif
        #ifndef ICT_OPENSSL_NO_WRAP
        EVP_CIPHER_TRANSLATE(aes_192_wrap)
        EVP_CIPHER_TRANSLATE(aes_192_wrap_pad)
        #endif
        #ifndef OPENSSL_NO_OCB
        EVP_CIPHER_TRANSLATE(aes_192_ocb)
        #endif
        EVP_CIPHER_TRANSLATE(aes_256_ecb)
        EVP_CIPHER_TRANSLATE(aes_256_cbc)
        EVP_CIPHER_TRANSLATE(aes_256_cfb1)
        EVP_CIPHER_TRANSLATE(aes_256_cfb8)
        EVP_CIPHER_TRANSLATE(aes_256_cfb128)
        EVP_CIPHER_TRANSLATE(aes_256_ofb)
        EVP_CIPHER_TRANSLATE(aes_256_ctr)
        #ifndef ICT_OPENSSL_NO_CCM
        EVP_CIPHER_TRANSLATE(aes_256_ccm)
        #endif
        #ifndef ICT_OPENSSL_NO_GCM
        EVP_CIPHER_TRANSLATE(aes_256_gcm)
        #endif
        #ifndef ICT_OPENSSL_NO_XTS
        EVP_CIPHER_TRANSLATE(aes_256_xts)
        #endif
        #ifndef ICT_OPENSSL_NO_WRAP
        EVP_CIPHER_TRANSLATE(aes_256_wrap)
        EVP_CIPHER_TRANSLATE(aes_256_wrap_pad)
        #endif
        #ifndef OPENSSL_NO_OCB
        EVP_CIPHER_TRANSLATE(aes_256_ocb)
        #endif
        #ifndef OPENSSL_NO_AES_CBC_HMAC
        EVP_CIPHER_TRANSLATE(aes_128_cbc_hmac_sha1)
        EVP_CIPHER_TRANSLATE(aes_256_cbc_hmac_sha1)
        EVP_CIPHER_TRANSLATE(aes_128_cbc_hmac_sha256)
        EVP_CIPHER_TRANSLATE(aes_256_cbc_hmac_sha256)
        #endif
        #ifndef OPENSSL_NO_ARIA
        EVP_CIPHER_TRANSLATE(aria_128_ecb)
        EVP_CIPHER_TRANSLATE(aria_128_cbc)
        EVP_CIPHER_TRANSLATE(aria_128_cfb1)
        EVP_CIPHER_TRANSLATE(aria_128_cfb8)
        EVP_CIPHER_TRANSLATE(aria_128_cfb128)
        EVP_CIPHER_TRANSLATE(aria_128_ctr)
        EVP_CIPHER_TRANSLATE(aria_128_ofb)
        #ifndef ICT_OPENSSL_NO_GCM
        EVP_CIPHER_TRANSLATE(aria_128_gcm)
        #endif
        #ifndef ICT_OPENSSL_NO_CCM
        EVP_CIPHER_TRANSLATE(aria_128_ccm)
        #endif
        EVP_CIPHER_TRANSLATE(aria_192_ecb)
        EVP_CIPHER_TRANSLATE(aria_192_cbc)
        EVP_CIPHER_TRANSLATE(aria_192_cfb1)
        EVP_CIPHER_TRANSLATE(aria_192_cfb8)
        EVP_CIPHER_TRANSLATE(aria_192_cfb128)
        EVP_CIPHER_TRANSLATE(aria_192_ctr)
        EVP_CIPHER_TRANSLATE(aria_192_ofb)
        #ifndef ICT_OPENSSL_NO_GCM
        EVP_CIPHER_TRANSLATE(aria_192_gcm)
        #endif
        #ifndef ICT_OPENSSL_NO_CCM
        EVP_CIPHER_TRANSLATE(aria_192_ccm)
        #endif
        EVP_CIPHER_TRANSLATE(aria_256_ecb)
        EVP_CIPHER_TRANSLATE(aria_256_cbc)
        EVP_CIPHER_TRANSLATE(aria_256_cfb1)
        EVP_CIPHER_TRANSLATE(aria_256_cfb8)
        EVP_CIPHER_TRANSLATE(aria_256_cfb128)
        EVP_CIPHER_TRANSLATE(aria_256_ctr)
        EVP_CIPHER_TRANSLATE(aria_256_ofb)
        #ifndef ICT_OPENSSL_NO_GCM
        EVP_CIPHER_TRANSLATE(aria_256_gcm)
        #endif
        #ifndef ICT_OPENSSL_NO_CCM
        EVP_CIPHER_TRANSLATE(aria_256_ccm)
        #endif
        #endif
        #ifndef OPENSSL_NO_CAMELLIA
        EVP_CIPHER_TRANSLATE(camellia_128_ecb)
        EVP_CIPHER_TRANSLATE(camellia_128_cbc)
        EVP_CIPHER_TRANSLATE(camellia_128_cfb1)
        EVP_CIPHER_TRANSLATE(camellia_128_cfb8)
        EVP_CIPHER_TRANSLATE(camellia_128_cfb128)
        EVP_CIPHER_TRANSLATE(camellia_128_ofb)
        EVP_CIPHER_TRANSLATE(camellia_128_ctr)
        EVP_CIPHER_TRANSLATE(camellia_192_ecb)
        EVP_CIPHER_TRANSLATE(camellia_192_cbc)
        EVP_CIPHER_TRANSLATE(camellia_192_cfb1)
        EVP_CIPHER_TRANSLATE(camellia_192_cfb8)
        EVP_CIPHER_TRANSLATE(camellia_192_cfb128)
        EVP_CIPHER_TRANSLATE(camellia_192_ofb)
        EVP_CIPHER_TRANSLATE(camellia_192_ctr)
        EVP_CIPHER_TRANSLATE(camellia_256_ecb)
        EVP_CIPHER_TRANSLATE(camellia_256_cbc)
        EVP_CIPHER_TRANSLATE(camellia_256_cfb1)
        EVP_CIPHER_TRANSLATE(camellia_256_cfb8)
        EVP_CIPHER_TRANSLATE(camellia_256_cfb128)
        EVP_CIPHER_TRANSLATE(camellia_256_ofb)
        EVP_CIPHER_TRANSLATE(camellia_256_ctr)
        #endif
        #ifndef OPENSSL_NO_CHACHA
        EVP_CIPHER_TRANSLATE(chacha20)
        #ifndef OPENSSL_NO_POLY1305
        EVP_CIPHER_TRANSLATE(chacha20_poly1305)
        #endif
        #endif
        #ifndef OPENSSL_NO_SEED
        EVP_CIPHER_TRANSLATE(seed_ecb)
        EVP_CIPHER_TRANSLATE(seed_cbc)
        EVP_CIPHER_TRANSLATE(seed_cfb128)
        EVP_CIPHER_TRANSLATE(seed_ofb)
        #endif
        #ifndef OPENSSL_NO_SM4
        EVP_CIPHER_TRANSLATE(sm4_ecb)
        EVP_CIPHER_TRANSLATE(sm4_cbc)
        EVP_CIPHER_TRANSLATE(sm4_cfb128)
        EVP_CIPHER_TRANSLATE(sm4_ofb)
        EVP_CIPHER_TRANSLATE(sm4_ctr)
        #endif
        default: break;
    }
    return(nullptr);
}
#undef EVP_CIPHER_TRANSLATE

static int add(const EVP_CIPHER *cipher){
    static std::set<const EVP_CIPHER *> added;
    if (!added.count(cipher)){ 
        int out=EVP_add_cipher(cipher);
        if (out==1) added.insert(cipher);
        return(out);
    }
    return(1);
}

password::password(const ict::safe::string & input,ict::cipher::type_t cipher_type,ict::hash::type_t hash_type,int count){
    const EVP_CIPHER * cipher=ict::cipher::translate(cipher_type);
    const EVP_MD * hash=ict::hash::translate(hash_type);
    if (cipher&&hash) {
        key.resize(EVP_MAX_KEY_LENGTH);
        iv.resize(EVP_MAX_IV_LENGTH);
        EVP_BytesToKey(
            cipher,
            hash,
            nullptr,
            (unsigned char *)input.c_str(),
            input.size(),
            count,
            (unsigned char *)key.data(),
            (unsigned char *)iv.data()
        );
    }
}

static int encrypt(const ict::safe::string & input,const password & pass,ict::safe::string & output,const EVP_CIPHER * cipher){
    int out;
    if (pass.ok()) {
        std::size_t size=input.size();
        std::size_t step=0x80*EVP_CIPHER_block_size(cipher);
        std::size_t offset_in=0;
        std::size_t offset_out=0;
        EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(),::EVP_CIPHER_CTX_free);
        {//Init
            out=EVP_EncryptInit_ex(ctx.get(),cipher,nullptr,pass.getKey(),pass.getIv());
            if (out!=1) throw std::runtime_error("EVP_EncryptInit_ex failed!!!");
            output.resize(input.size()+EVP_MAX_IV_LENGTH);
        }
        while(offset_in<size){//Update
            int len_in=(int)(((size-offset_in)<step)?(size-offset_in):step);
            int len_out=len_in+EVP_MAX_IV_LENGTH;
            out=EVP_EncryptUpdate(ctx.get(),(unsigned char*)output.data()+offset_out,&len_out,(const unsigned char*)input.data()+offset_in,len_in);
            if (out!=1) throw std::runtime_error("EVP_EncryptUpdate failed!!!");            
            offset_in+=step;
            offset_out+=len_out;
        }
        {//Final
            int len_out=(int)(output.size()-offset_out);
            out=EVP_EncryptFinal_ex(ctx.get(),(unsigned char*)output.data()+offset_out,&len_out);
            if (out!=1) throw std::runtime_error("EVP_EncryptFinal_ex failed!!!");
            offset_out+=len_out;
            output.resize(offset_out);
        }
    } else {
        return(-1);
    }
    return(0);
}
int encrypt(const ict::safe::string & input,const password & pass,ict::safe::string & output,type_t cipher_type){
    int out;
    const EVP_CIPHER * cipher(translate(cipher_type));
    if (!cipher) throw std::invalid_argument("Cipher not implemented!!!");
    out=add(cipher);
    if (out!=1) throw std::runtime_error("EVP_add_cipher failed!!!");
    out=encrypt(input,pass,output,cipher);
    return(out);
}
int encrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::safe::string & output,type_t cipher_type){
    password p(pass,cipher_type);
    return(encrypt(input,p,output,cipher_type));
}
static int decrypt(const ict::safe::string & input,const password & pass,ict::safe::string & output,const EVP_CIPHER * cipher){
    int out;
    if (pass.ok()) {
        std::size_t size=input.size();
        std::size_t step=0x80*EVP_CIPHER_block_size(cipher);
        std::size_t offset_in=0;
        std::size_t offset_out=0;
        EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(),::EVP_CIPHER_CTX_free);
        {//Init
            out=EVP_DecryptInit_ex(ctx.get(),cipher,nullptr,pass.getKey(),pass.getIv());
            if (out!=1) throw std::runtime_error("EVP_DecryptInit_ex failed !!!");
            output.resize(size+EVP_MAX_IV_LENGTH);
        }
        while(offset_in<size){//Update
            int len_in=(int)(((size-offset_in)<step)?(size-offset_in):step);
            int len_out=len_in+EVP_MAX_IV_LENGTH;
            out=EVP_DecryptUpdate(ctx.get(),(unsigned char*)output.data()+offset_out,&len_out,(const unsigned char*)input.data()+offset_in,len_in);
            if (out!=1) throw std::runtime_error("EVP_DecryptUpdate failed !!!");
            offset_in+=step;
            offset_out+=len_out;
        }
        {//Final
            int len_out=(int)(output.size()-offset_out);
            out=EVP_DecryptFinal_ex(ctx.get(),(unsigned char*)output.data()+offset_out,&len_out);
            if (out!=1) throw std::runtime_error("EVP_DecryptFinal_ex failed !!!");
            offset_out+=len_out;
            output.resize(offset_out);
        }
    } else {
        return(-1);
    }
    return(0);
}
int decrypt(const ict::safe::string & input,const password & pass,ict::safe::string & output,type_t cipher_type){
    int out;
    const EVP_CIPHER * cipher(translate(cipher_type));
    if (!cipher) throw std::invalid_argument("Cipher not implemented!!!");
    out=add(cipher);
    if (out!=1) throw std::runtime_error("EVP_add_cipher failed!!!");
    out=decrypt(input,pass,output,cipher);
    return(out);
}
int decrypt(const ict::safe::string & input,const ict::safe::string & pass,ict::safe::string & output,type_t cipher_type){
    password p(pass,cipher_type);
    return(decrypt(input,p,output,cipher_type));
}
//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
#include <cstdlib>
static int test_cipher(ict::cipher::type_t type){
    std::size_t n=0;
    const static std::size_t x(100);
    ict::safe::string input,key,encrypted,decrypted;
    input.resize(x*0x100+(std::rand()%(x/2)));
    key.resize(1+std::rand()%(20));
    for (auto &c:input) c=std::rand()%0x80;
    for (auto &c:key) c='0'+std::rand()%('z'-'0');
    if (ict::cipher::encrypt(input,key,encrypted,type)!=0) return(1);
    if (ict::cipher::decrypt(encrypted,key,decrypted,type)!=0) return(2);
    if (input!=decrypted){
        if (input.size()<decrypted.size()){
            if (input==decrypted.substr(0,input.size()))
                std::cout<<"Input("<<input.size()<<") zawiera się w decrypted("<<decrypted.size()<<")"<<std::endl;
        } else {
            if (decrypted==input.substr(0,decrypted.size()))
                std::cout<<"Decrypted("<<decrypted.size()<<") zawiera się w input("<<input.size()<<")"<<std::endl;
        }
        return(3);
    }
    for (std::size_t k=0;k<input.size();k++) if (input.at(k)==encrypted.at(k)) n++;
    if ((2*x)<n) return(4);
    for (unsigned int k=0;k<0x100;k++){
        n=0;
        for (auto &c:encrypted) if ((unsigned char)c==k) n++;
        if ((2*x)<n) return(5);
        if (n<(x/2)) return(6);
    }
    return(0);
}
#define EVP_CIPHER_TEST(type) \
REGISTER_TEST(cipher,tc_##type){ \
    if (ict::cipher::translate(ict::cipher::type_t::type)){ \
        return(test_cipher(ict::cipher::type_t::type)); \
    } \
    return(0); \
}
EVP_CIPHER_TEST(des_ecb)
EVP_CIPHER_TEST(des_ede)
EVP_CIPHER_TEST(des_ede3)
EVP_CIPHER_TEST(des_ede_ecb)
EVP_CIPHER_TEST(des_ede3_ecb)
EVP_CIPHER_TEST(des_cfb64)
EVP_CIPHER_TEST(des_cfb1)
EVP_CIPHER_TEST(des_cfb8)
EVP_CIPHER_TEST(des_ede_cfb64)
EVP_CIPHER_TEST(des_ede3_cfb64)
EVP_CIPHER_TEST(des_ede3_cfb1)
EVP_CIPHER_TEST(des_ede3_cfb8)
EVP_CIPHER_TEST(des_ofb)
EVP_CIPHER_TEST(des_ede_ofb)
EVP_CIPHER_TEST(des_ede3_ofb)
EVP_CIPHER_TEST(des_cbc)
EVP_CIPHER_TEST(des_ede_cbc)
EVP_CIPHER_TEST(des_ede3_cbc)
EVP_CIPHER_TEST(desx_cbc)
EVP_CIPHER_TEST(des_ede3_wrap)
EVP_CIPHER_TEST(rc4)
EVP_CIPHER_TEST(rc4_40)
EVP_CIPHER_TEST(rc4_hmac_md5)
EVP_CIPHER_TEST(idea_ecb)
EVP_CIPHER_TEST(idea_cfb64)
EVP_CIPHER_TEST(idea_ofb)
EVP_CIPHER_TEST(idea_cbc)
EVP_CIPHER_TEST(rc2_ecb)
EVP_CIPHER_TEST(rc2_cbc)
EVP_CIPHER_TEST(rc2_40_cbc)
EVP_CIPHER_TEST(rc2_64_cbc)
EVP_CIPHER_TEST(rc2_cfb64)
EVP_CIPHER_TEST(rc2_ofb)
EVP_CIPHER_TEST(bf_ecb)
EVP_CIPHER_TEST(bf_cbc)
EVP_CIPHER_TEST(bf_cfb64)
EVP_CIPHER_TEST(bf_ofb)
EVP_CIPHER_TEST(cast5_ecb)
EVP_CIPHER_TEST(cast5_cbc)
EVP_CIPHER_TEST(cast5_cfb64)
EVP_CIPHER_TEST(cast5_ofb)
EVP_CIPHER_TEST(rc5_32_12_16_cbc)
EVP_CIPHER_TEST(rc5_32_12_16_ecb)
EVP_CIPHER_TEST(rc5_32_12_16_cfb64)
EVP_CIPHER_TEST(rc5_32_12_16_ofb)
EVP_CIPHER_TEST(aes_128_ecb)
EVP_CIPHER_TEST(aes_128_cbc)
EVP_CIPHER_TEST(aes_128_cfb1)
EVP_CIPHER_TEST(aes_128_cfb8)
EVP_CIPHER_TEST(aes_128_cfb128)
EVP_CIPHER_TEST(aes_128_ofb)
EVP_CIPHER_TEST(aes_128_ctr)
EVP_CIPHER_TEST(aes_128_ccm)
EVP_CIPHER_TEST(aes_128_gcm)
EVP_CIPHER_TEST(aes_128_xts)
EVP_CIPHER_TEST(aes_128_wrap)
EVP_CIPHER_TEST(aes_128_wrap_pad)
EVP_CIPHER_TEST(aes_128_ocb)
EVP_CIPHER_TEST(aes_192_ecb)
EVP_CIPHER_TEST(aes_192_cbc)
EVP_CIPHER_TEST(aes_192_cfb1)
EVP_CIPHER_TEST(aes_192_cfb8)
EVP_CIPHER_TEST(aes_192_cfb128)
EVP_CIPHER_TEST(aes_192_ofb)
EVP_CIPHER_TEST(aes_192_ctr)
EVP_CIPHER_TEST(aes_192_ccm)
EVP_CIPHER_TEST(aes_192_gcm)
EVP_CIPHER_TEST(aes_192_wrap)
EVP_CIPHER_TEST(aes_192_wrap_pad)
EVP_CIPHER_TEST(aes_192_ocb)
EVP_CIPHER_TEST(aes_256_ecb)
EVP_CIPHER_TEST(aes_256_cbc)
EVP_CIPHER_TEST(aes_256_cfb1)
EVP_CIPHER_TEST(aes_256_cfb8)
EVP_CIPHER_TEST(aes_256_cfb128)
EVP_CIPHER_TEST(aes_256_ofb)
EVP_CIPHER_TEST(aes_256_ctr)
EVP_CIPHER_TEST(aes_256_ccm)
EVP_CIPHER_TEST(aes_256_gcm)
EVP_CIPHER_TEST(aes_256_xts)
EVP_CIPHER_TEST(aes_256_wrap)
EVP_CIPHER_TEST(aes_256_wrap_pad)
EVP_CIPHER_TEST(aes_256_ocb)
EVP_CIPHER_TEST(aes_128_cbc_hmac_sha1)
EVP_CIPHER_TEST(aes_256_cbc_hmac_sha1)
EVP_CIPHER_TEST(aes_128_cbc_hmac_sha256)
EVP_CIPHER_TEST(aes_256_cbc_hmac_sha256)
EVP_CIPHER_TEST(aria_128_ecb)
EVP_CIPHER_TEST(aria_128_cbc)
EVP_CIPHER_TEST(aria_128_cfb1)
EVP_CIPHER_TEST(aria_128_cfb8)
EVP_CIPHER_TEST(aria_128_cfb128)
EVP_CIPHER_TEST(aria_128_ctr)
EVP_CIPHER_TEST(aria_128_ofb)
EVP_CIPHER_TEST(aria_128_gcm)
EVP_CIPHER_TEST(aria_128_ccm)
EVP_CIPHER_TEST(aria_192_ecb)
EVP_CIPHER_TEST(aria_192_cbc)
EVP_CIPHER_TEST(aria_192_cfb1)
EVP_CIPHER_TEST(aria_192_cfb8)
EVP_CIPHER_TEST(aria_192_cfb128)
EVP_CIPHER_TEST(aria_192_ctr)
EVP_CIPHER_TEST(aria_192_ofb)
EVP_CIPHER_TEST(aria_192_gcm)
EVP_CIPHER_TEST(aria_192_ccm)
EVP_CIPHER_TEST(aria_256_ecb)
EVP_CIPHER_TEST(aria_256_cbc)
EVP_CIPHER_TEST(aria_256_cfb1)
EVP_CIPHER_TEST(aria_256_cfb8)
EVP_CIPHER_TEST(aria_256_cfb128)
EVP_CIPHER_TEST(aria_256_ctr)
EVP_CIPHER_TEST(aria_256_ofb)
EVP_CIPHER_TEST(aria_256_gcm)
EVP_CIPHER_TEST(aria_256_ccm)
EVP_CIPHER_TEST(camellia_128_ecb)
EVP_CIPHER_TEST(camellia_128_cbc)
EVP_CIPHER_TEST(camellia_128_cfb1)
EVP_CIPHER_TEST(camellia_128_cfb8)
EVP_CIPHER_TEST(camellia_128_cfb128)
EVP_CIPHER_TEST(camellia_128_ofb)
EVP_CIPHER_TEST(camellia_128_ctr)
EVP_CIPHER_TEST(camellia_192_ecb)
EVP_CIPHER_TEST(camellia_192_cbc)
EVP_CIPHER_TEST(camellia_192_cfb1)
EVP_CIPHER_TEST(camellia_192_cfb8)
EVP_CIPHER_TEST(camellia_192_cfb128)
EVP_CIPHER_TEST(camellia_192_ofb)
EVP_CIPHER_TEST(camellia_192_ctr)
EVP_CIPHER_TEST(camellia_256_ecb)
EVP_CIPHER_TEST(camellia_256_cbc)
EVP_CIPHER_TEST(camellia_256_cfb1)
EVP_CIPHER_TEST(camellia_256_cfb8)
EVP_CIPHER_TEST(camellia_256_cfb128)
EVP_CIPHER_TEST(camellia_256_ofb)
EVP_CIPHER_TEST(camellia_256_ctr)
EVP_CIPHER_TEST(chacha20)
EVP_CIPHER_TEST(chacha20_poly1305)
EVP_CIPHER_TEST(seed_ecb)
EVP_CIPHER_TEST(seed_cbc)
EVP_CIPHER_TEST(seed_cfb128)
EVP_CIPHER_TEST(seed_ofb)
EVP_CIPHER_TEST(sm4_ecb)
EVP_CIPHER_TEST(sm4_cbc)
EVP_CIPHER_TEST(sm4_cfb128)
EVP_CIPHER_TEST(sm4_ofb)
EVP_CIPHER_TEST(sm4_ctr)
#undef EVP_CIPHER_TEST
#endif
//===========================================