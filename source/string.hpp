//! @file
//! @brief OpenSSL safe string module - header file.
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
#ifndef _OPENSSL_STRING_HEADER
#define _OPENSSL_STRING_HEADER
//============================================
#include <string>
#include <memory>
#include <stdlib.h>
#include <string.h>
//============================================
namespace ict { namespace  safe {
//============================================
template <class T> class allocator : std::allocator<T>{
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef T        value_type;
    template<typename R> struct rebind { typedef allocator<R> other;};
    allocator() noexcept : std::allocator<T>(){}
    allocator (const allocator& alloc) noexcept: std::allocator<T>(alloc){}
    template <class U> allocator (const allocator<U>& alloc) noexcept : std::allocator<T>(alloc){}
    pointer allocate (size_type n, std::allocator<void>::const_pointer hint=0){
        return(std::allocator<T>::allocate(n,hint));
    }
    void deallocate(T* p,size_type n) {
        ::memset(p,std::rand()%0x100,n*sizeof(T));
        std::allocator<T>::deallocate(p,n);
    }
    friend bool operator==(const allocator&,const allocator&) noexcept {return(true);}
    friend bool operator!=(const allocator&,const allocator&) noexcept {return(false);}
    template<typename A> inline bool operator==(const allocator<A>&) noexcept {return(true);}
    template<typename A> inline bool operator!=(const allocator<A>&) noexcept {return(false);}
};
template <class charT,class traits=std::char_traits<charT>> using basic_string=std::basic_string<charT,traits,allocator<charT>>;
typedef basic_string<char> string;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;
typedef basic_string<wchar_t> wstring;
//============================================
} }
//============================================
#endif