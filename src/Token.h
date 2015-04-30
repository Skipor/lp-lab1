//
// Created by  Vladimir Skipor on 28/04/15.
//

#ifndef LP_LAB1_NON_TERMINAL_H
#define LP_LAB1_NON_TERMINAL_H

#include <string>
#include <exception>
#include <cstdlib>


enum class Token : int{
  UNDEFINED = 0,
  VAR,
  NAME,
  TYPE,
  COMMA,
  COLON,
  SEMICOLON,
  END,
};

namespace std {
  inline string to_string(Token t) {
    switch (t) {
      case Token::UNDEFINED : return "UNDEFINED";
      case Token::VAR : return "VAR";
      case Token::NAME : return "NAME";
      case Token::TYPE : return "TYPE";
      case Token::COMMA : return ",";
      case Token::COLON : return ":";
      case Token::SEMICOLON : return ";";
      case Token::END : return "END";
      default: std::abort();
    }
  }
}


#endif //LP_LAB1_NON_TERMINAL_H
