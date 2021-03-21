//! @file
//! @brief Padding module - Source file.
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
#include "padding.hpp"
#include <stdexcept>
#include <cstdlib>
//============================================
namespace ict { namespace  padding {  
//============================================
// https://www.di-mgt.com.au/cryptopad.html
//============================================
bool guess(const ict::safe::string & input,const std::size_t & blockSize){
    std::size_t s=input.size();
    if (!blockSize) throw std::invalid_argument("Block size must be greater than zero!!!");
    if (s%blockSize) throw std::invalid_argument("Input size must be a multiple of the block size ("+std::to_string(blockSize)+")!!!");
    if (s){
        switch (input.back()){
            case ' ':
            case '\0':
                return(true);
            default:
                if (((unsigned char)input.back())<=blockSize) return(true);
                break;
        }
    }
    return(false);
}
void add(const ict::safe::string & input,ict::safe::string & output,const std::size_t & blockSize){
    std::size_t s=input.size();
    if (!blockSize) throw std::invalid_argument("Block size must be greater than zero!!!");
    output.clear();
    {
        std::size_t p=blockSize-s%blockSize;
        output=input;
        output.resize(s+p);
        s=output.size()-1;
        output[s]=p;
        for (std::size_t i=1;i<p;i++){
            output[s-i]=std::rand()%0x100;
        }
    }
}
void remove(const ict::safe::string & input,ict::safe::string & output,const std::size_t & blockSize){
    std::size_t s=input.size();
    if (guess(input,blockSize)){
        output=input;
        switch (output.back()){
            case ' ':{
                for (std::size_t i=0;i<blockSize;i++) if (output.back()==' '){
                    output.pop_back();
                } else {
                    break;
                }
            } return;
            case '\0':{
                for (std::size_t i=0;i<blockSize;i++) if (output.back()=='\0'){
                    output.pop_back();
                } else if (((unsigned char)(output.back())==0x80)) {
                    output.pop_back();
                    break;
                } else {
                    break;
                }
            } return;
            default:{
                unsigned char p=(unsigned char)input.back();
                if (p<=blockSize) {
                    for (unsigned char i=0;i<p;i++) 
                        output.pop_back();
                    return;
                }
            } break;
        }
    }
    throw std::invalid_argument("Unable to find padding in input!!!");
}
//===========================================
} }
//===========================================
#ifdef ENABLE_TESTING
#include "test.hpp"
REGISTER_TEST(padding,tc1){
    int out=0;
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7'});
        if (ict::padding::guess(input,8)!=false){
            out=1;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6',1});
        if (ict::padding::guess(input,8)!=true){
            out=2;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','_',2});
        if (ict::padding::guess(input,8)==false){
            out=3;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','_','_',3});
        if (ict::padding::guess(input,8)!=true){
            out=4;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3','4','5','6','7'});
        if (ict::padding::guess(input,8)!=false){
            out=5;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3','_','_','_',4});
        if (ict::padding::guess(input,8)!=true){
            out=6;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3',' ',' ',' ',' '});
        if (ict::padding::guess(input,8)!=true){
            out=7;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3',0,0,0,0});
        if (ict::padding::guess(input,8)!=true){
            out=8;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3',(char)0x80,0,0,0});
        if (ict::padding::guess(input,8)!=true){
            out=9;
        }
    }
    return(out);
}
REGISTER_TEST(padding,tc2){
    int out=0;
    if (out==0){
        ict::safe::string input("01234567");
        ict::safe::string output;
        ict::padding::add(input,output,8);
        if (output.size()!=16){
            out=1;
        }
        if (input!=output.substr(0,8)){
            out=2;
        }
        if (output.back()!=8){
            out=3;
        }
    }
    if (out==0){
        ict::safe::string input("01234567012");
        ict::safe::string output;
        ict::padding::add(input,output,8);
        if (output.size()!=16){
            out=4;
        }
        if (input!=output.substr(0,11)){
            out=5;
        }
        if (output.back()!=5){
            out=6;
        }
    }
    if (out==0){
        ict::safe::string input("012345670123456");
        ict::safe::string output;
        ict::padding::add(input,output,8);
        if (output.size()!=16){
            out=7;
        }
        if (input!=output.substr(0,15)){
            out=8;
        }
        if (output.back()!=1){
            out=9;
        }
    }
    return(out);
}
REGISTER_TEST(padding,tc3){
    int out=0;
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6',1});
        ict::safe::string output;
        ict::padding::remove(input,output,8);
        if (output!=input.substr(0,7)){
            out=1;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','_',2});
        ict::safe::string output;
        ict::padding::remove(input,output,8);
        if (output!=input.substr(0,6)){
            out=2;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','_','_',3});
        ict::safe::string output;
        ict::padding::remove(input,output,8);
        if (output!=input.substr(0,5)){
            out=3;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3','_','_','_',4});
        ict::safe::string output;
        ict::padding::remove(input,output,8);
        if (output!=input.substr(0,12)){
            out=4;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3',' ',' ',' ',' '});
        ict::safe::string output;
        ict::padding::remove(input,output,8);
        if (output!=input.substr(0,12)){
            out=5;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3',0,0,0,0});
        ict::safe::string output;
        ict::padding::remove(input,output,8);
        if (output!=input.substr(0,12)){
            out=6;
        }
    }
    if (out==0){
        ict::safe::string input({'0','1','2','3','4','5','6','7','0','1','2','3',(char)0x80,0,0,0});
        ict::safe::string output;
        ict::padding::remove(input,output,8);
        if (output!=input.substr(0,12)){
            out=7;
        }
    }
    return(out);
}
REGISTER_TEST(padding,tc4){
    int out=0;
    if (out==0){
        ict::safe::string input;
        ict::safe::string output1,output2;
        input.resize(100+std::rand()%100);
        for (auto & c: input) c=std::rand()%0x100;
        ict::padding::add(input,output1,8);
        ict::padding::remove(output1,output2,8);
        if (input!=output1.substr(0,input.size())){
            out=1;
        }
        if (input!=output2){
            out=2;
        }
    }
    return(out);
}
#endif
//===========================================