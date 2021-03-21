//! @file
//! @brief Padding module - header file.
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
#ifndef _PADDING_HEADER
#define _PADDING_HEADER
//============================================
#include "string.hpp"
//============================================
namespace ict { namespace  padding { 
//===========================================
//! 
//! @brief Zgaduje, czy na końcu znajduje się wypełnienie (pewności nie ma - możliwe są wskazania fałszywie pozytywne).
//! 
//! @param input Wejściowy ciąg bajtów (jego rozmiar musi być wielokrotnością rozmiaru bloku).
//! @param blockSize Rozmiar bloku.
//! @return true Prawdopodobnie jest wypełnienie.
//! @return false Na pewno nie ma wypełnienia.
//! 
bool guess(const ict::safe::string & input,const std::size_t & blockSize);
//! 
//! @brief Dodaje wypełnienie na końcu ciągu bajtów.
//! 
//! @param input Wejściowy ciąg bajtów.
//! @param output Wyjściowy ciąg bajtów - uzupełniny o wypełnienie (jego rozmiar jest wielokrotnością rozmiaru bloku).
//! @param blockSize Rozmiar bloku.
//! 
void add(const ict::safe::string & input,ict::safe::string & output,const std::size_t & blockSize);
//! 
//! @brief Usuwa wypełnienie na końcu ciągu bajtów.
//! 
//! @param input Wejściowy ciąg bajtów (jego rozmiar musi być wielokrotnością rozmiaru bloku).
//! @param output Wyjściowy ciąg bajtów z usuniętym wypełnieniem.
//! @param blockSize Rozmiar bloku. 
//! 
void remove(const ict::safe::string & input,ict::safe::string & output,const std::size_t & blockSize);
//! 
//! @brief  Dodaje wypełnienie na końcu ciągu bajtów.
//! 
//! @param input  Wejściowy ciąg bajtów.
//! @param blockSize Rozmiar bloku.
//! @return Wyjściowy ciąg bajtów - uzupełniny o wypełnienie (jego rozmiar jest wielokrotnością rozmiaru bloku).
//! 
inline ict::safe::string add(const ict::safe::string & input,const std::size_t & blockSize){
    ict::safe::string output;
    add(input,output,blockSize);
    return(output);
}
//! 
//! @brief Usuwa wypełnienie na końcu ciągu bajtów.
//! 
//! @param input Wejściowy ciąg bajtów (jego rozmiar musi być wielokrotnością rozmiaru bloku).
//! @param blockSize  Rozmiar bloku.
//! @return Wyjściowy ciąg bajtów z usuniętym wypełnieniem. 
//! 
inline ict::safe::string remove(const ict::safe::string & input,const std::size_t & blockSize){
    ict::safe::string output;
    remove(input,output,blockSize);
    return(output);
}
//===========================================
} }
//============================================
#endif