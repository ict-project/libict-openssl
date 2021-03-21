//! @file
//! @brief Test module - Source file.
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
//============================================
#include "test.hpp"
#include "all.hpp"
#include <algorithm>
//============================================
namespace ict { namespace test {
//===========================================
std::vector<TC*> & TC::getList(){
  static std::vector<TC*> list;
  return(list);
}
TC::TC(const tag_list_t & tags_in,test_fun_t fun_in,const char * file_in,int line_in):tags(tags_in),fun(fun_in),file(file_in),line(line_in){
  getList().push_back(this);
}
bool TC::testTags(const tag_list_t & tags_in) const{
  for (const std::string & in : tags_in) {
    auto it=std::find(tags.begin(),tags.end(),in);
    if (it==tags.end()) return(false);
  }
  return(true);
}
std::string TC::printTags(const tag_list_t & tags_in,char separator) const{
  std::string out;
  bool first=true;
  for (const std::string & in : tags_in) {
    if (first){
      first=false;
    } else {
      out+=separator;
    }
    out+=in;
  }
  return(out);
}
std::string TC::printTags(char separator) const{
  return(printTags(tags,separator));
}
int TC::runThis(const tag_list_t & tags_in) const{
  if (testTags(tags_in)){
    int out=0;
    if (fun) {
      std::cout<<"## TC: "<<printTags()<<std::endl;
      out=fun();
      std::cout<<"RESULT: "<<(out?"ERROR":"OK")<<std::endl;
      if (out){
        std::cout<<" FILE="<<file<<", LINE="<<line<<", OUT="<<out<<std::endl;
      }
      std::cout<<std::endl;
    }
    return(out);
  }
  return(0);
}
int TC::run(const tag_list_t & tags_in){
  if (tags_in.size()) if (tags_in.at(0)=="-"){
    for (const TC * tc : getList()) {
      std::cout<<"add_test(NAME "<<tc->printTags('-')<<" COMMAND ${PROJECT_NAME}-test "<<tc->printTags(' ')<<")"<<std::endl;
    }
    return(0);
  }
  for (const TC * tc : getList()) {
    int out=tc->runThis(tags_in);
    if (out) return(out);
  }
  return(0);
}
//============================================
// Source: https://pl.wikipedia.org/wiki/Pangram#j.C4.99zyk_polski
const test_string_t test_string({
  "Pchnąć w tę łódź jeża lub ośm skrzyń fig.",
  "Pójdźże, kiń tę chmurność w głąb flaszy!",
  "Myślę: Fruń z płacht gąsko, jedź wbić nóż.",
  "Dość błazeństw, żrą mój pęk luźnych fig.",
  "W niżach mógł zjeść truflę koń bądź psy.",
  "Dość gróźb fuzją, klnę, pych i małżeństw!",
  "Pójdź w loch zbić małżeńską gęś futryn!",
  "Filmuj rzeź żądań, pość, gnęb chłystków!.",
  "O, mógłże sęp chlań wyjść furtką bździn.",
  "Mężny bądź, chroń pułk twój i sześć flag.",
  "Chwyć małżonkę, strój bądź pleśń z fugi.",
  "Jeż wlókł gęś. Uf! Bądź choć przy nim, stań!",
  "Wójt dźgnął boży puch, sześć frań, milkę.",
  "Mknął boży puch. Jeść stóg z lędźwi Frań?",
  "Puść mą dłoń! Gnij schab, frytkę! Zwóź żel!",
  "Tknę łój, wapń. Dość! Uf! Gryź chleb, miąższ!",
  "Znajdź pchły, wróżko! Film \"Teść\" gębą suń!",
  "Sklną chów żab? Jim, puść dłoń! Zgryź fetę!",
  "Aj, pech! Struś dźgnął ćmę FBI! Koń lży wóz.",
  "Tchórz w KGB. Sądź płoć! Fajny mężuś i leń.",
  "Bądź waść gej, chroń kumpli! Złóż syf, tnę!",
  "Struś czknął. Pędź, bij ćmy! Że ów golf Hań?",
  "Czyść sejf glinom! W łóżku Hań ...pędź, trąb!",
  "Strząść puch nimfy w łój kań? Boże, ględź!",
  "W Mińsku lżą naftę Jóź. Gość brzydł. Pech!",
  "Sznur śliw. Chłód gąb. Pot męk. Jaźń żyć. Fe!",
  "クイックブラウンキツネは怠惰な犬の上を飛びます。",
});
const test_wstring_t test_wstring({
  L"Pchnąć w tę łódź jeża lub ośm skrzyń fig.",
  L"Pójdźże, kiń tę chmurność w głąb flaszy!",
  L"Myślę: Fruń z płacht gąsko, jedź wbić nóż.",
  L"Dość błazeństw, żrą mój pęk luźnych fig.",
  L"W niżach mógł zjeść truflę koń bądź psy.",
  L"Dość gróźb fuzją, klnę, pych i małżeństw!",
  L"Pójdź w loch zbić małżeńską gęś futryn!",
  L"Filmuj rzeź żądań, pość, gnęb chłystków!.",
  L"O, mógłże sęp chlań wyjść furtką bździn.",
  L"Mężny bądź, chroń pułk twój i sześć flag.",
  L"Chwyć małżonkę, strój bądź pleśń z fugi.",
  L"Jeż wlókł gęś. Uf! Bądź choć przy nim, stań!",
  L"Wójt dźgnął boży puch, sześć frań, milkę.",
  L"Mknął boży puch. Jeść stóg z lędźwi Frań?",
  L"Puść mą dłoń! Gnij schab, frytkę! Zwóź żel!",
  L"Tknę łój, wapń. Dość! Uf! Gryź chleb, miąższ!",
  L"Znajdź pchły, wróżko! Film \"Teść\" gębą suń!",
  L"Sklną chów żab? Jim, puść dłoń! Zgryź fetę!",
  L"Aj, pech! Struś dźgnął ćmę FBI! Koń lży wóz.",
  L"Tchórz w KGB. Sądź płoć! Fajny mężuś i leń.",
  L"Bądź waść gej, chroń kumpli! Złóż syf, tnę!",
  L"Struś czknął. Pędź, bij ćmy! Że ów golf Hań?",
  L"Czyść sejf glinom! W łóżku Hań ...pędź, trąb!",
  L"Strząść puch nimfy w łój kań? Boże, ględź!",
  L"W Mińsku lżą naftę Jóź. Gość brzydł. Pech!",
  L"Sznur śliw. Chłód gąb. Pot męk. Jaźń żyć. Fe!",
  L"クイックブラウンキツネは怠惰な犬の上を飛びます。",
});
//============================================
}}
//============================================
ict::test::tag_list_t tag_list;
//=================================================
int main(int argc,const char **argv){
  //std::string locale(setlocale(LC_ALL,std::getenv("LANG")));
  std::string locale(setlocale(LC_ALL,"C"));
  for (std::size_t i=1;i<argc;i++) {
    tag_list.emplace_back(argv[i]);
  }
  return(ict::test::TC::run(tag_list));
}
//===========================================
