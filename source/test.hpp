//! @file
//! @brief Test module -header file.
//! @author Mariusz Ornowski (mariusz.ornowski@ict-project.pl)
//! @version 1.0
//! @date 2016-2017
//! @copyright ICT-Project Mariusz Ornowski (ict-project.pl)
/* **************************************************************
Copyright (c) 2016-2017, ICT-Project Mariusz Ornowski (ict-project.pl)
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
#ifndef _TEST_HEADER
#define _TEST_HEADER
//============================================
#include <string>
#include <vector>
#include <iostream>
//============================================
#define REGISTER_TEST(ns,tc) \
static int test_##tc(); \
namespace ict { namespace ns { \
 ict::test::TC tc({"ict",#ns,#tc},test_##tc,__FILE__,__LINE__); \
}} \
static int test_##tc()
//============================================
namespace ict { namespace test {
//===========================================
typedef std::vector<std::string> tag_list_t;
typedef int (*test_fun_t)();
typedef std::vector<std::string> test_string_t;
typedef std::vector<std::wstring> test_wstring_t;
//===========================================
class TC {
private:
  static std::vector<TC*> & getList();
  const tag_list_t tags;
  test_fun_t fun;
  const char * file;
  int line;
  int runThis(const tag_list_t & tags_in) const;
  bool testTags(const tag_list_t & tags_in) const;
  std::string printTags(const tag_list_t & tags_in,char separator='-') const;
public:
  TC(const tag_list_t & tags_in,test_fun_t fun_in,const char * file_in,int line_in);
  static int run(const tag_list_t & tags_in);
  std::string printTags(char separator='-') const;
};
//============================================
extern const test_string_t test_string;
extern const test_wstring_t test_wstring;
//============================================
}}
//===========================================
#endif