//
// Created by  Vladimir Skipor on 28/04/15.
//

#ifndef LP_LAB1_LEXER_H
#define LP_LAB1_LEXER_H

#include "Token.h"
#include <array>
#include <regex>
#include <iostream>
#include <sstream>





class Lexer {


public:
  Lexer(std::istream& istream) : istream_(istream), token_to_regex(GetTokenToRegex()),
                                 all_tokens_regex(GetAllTokensRegex()) {
    if (istream.fail()) {
      throw std::runtime_error("failed to use stream");
    }
    NextToken();
  }

  Token NextToken() {
    static std::string current_parsing_string;
    while (next_token_it_ == end_token_it_) {
      if (istream_.bad()) {
        throw std::runtime_error("istream fail");
      }
      if (istream_.eof()) {
        if (current_token_ == Token::END) {
          throw std::logic_error("take token after end");
        } else {
          current_lex_ = "$";
          return current_token_ = Token::END;
        }
      }
      std::getline(istream_, current_parsing_string);
      next_token_it_ = std::sregex_token_iterator(
          current_parsing_string.begin(),
          current_parsing_string.end(),
          all_tokens_regex
      );
    }

    current_lex_ = *next_token_it_;
    ++next_token_it_;
    return current_token_ = GetTokenByLex(current_lex_);
  }

  Token current_token() const {
    return current_token_;
  }

  const std::string& current_lex() const {
    return current_lex_;
  }





  Token GetTokenByLex(const std::string& lex) const {
    for (auto token_regex_pair : token_to_regex) {
      if (std::regex_match(lex, token_regex_pair.second)) {
        return token_regex_pair.first;
      }
    }
    std::abort();
  }

private:
  std::istream& istream_;
  Token current_token_ = Token::UNDEFINED;
  std::string current_lex_;
  std::sregex_token_iterator next_token_it_;
  const std::sregex_token_iterator end_token_it_;
  const std::vector<std::pair<Token, std::string>> token_to_str_regex{
      {
          {Token::VAR, "(\\bvar\\b)"},
          {Token::TYPE, "(\\bchar\\b)|(\\breal)|(\\binteger\\b)|(\\bstring\\b)|(\\bboolean\\b)"},
          {Token::COLON, "(:)"},
          {Token::SEMICOLON, "(;)"},
          {Token::COMMA, "(,)"},
          {Token::NAME, "([a-zA-Z]\\w*)"},
          {Token::UNDEFINED, "(\\S+)"}
      }
  };

  const std::vector<std::pair<Token, std::regex>> token_to_regex;
  const std::regex all_tokens_regex;

  std::vector<std::pair<Token, std::regex>> GetTokenToRegex() {
    std::vector<std::pair<Token, std::regex>> result;
    for (auto token_str_pair : token_to_str_regex) {
      result.emplace_back(token_str_pair.first, std::regex(token_str_pair.second));
    }
    return result;
  }

  std::regex GetAllTokensRegex() {
    std::stringstream regex_sstream;
    bool add_or = false;
    for (auto token_str_pair : token_to_str_regex) {
      if (add_or) {
        regex_sstream << '|';
      }
      add_or = true;
      regex_sstream << token_str_pair.second;
    }
//    std::cout << regex_sstream.str() << std::endl;
    return std::regex(regex_sstream.str());
  }

};


#endif //LP_LAB1_LEXER_H
