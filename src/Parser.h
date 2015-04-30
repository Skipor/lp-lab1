//
// Created by  Vladimir Skipor on 29/04/15.
//

#ifndef LP_LAB1_PARSER_H
#define LP_LAB1_PARSER_H

#include "Lexer.h"
#include "Tree.h"


class ParseError : public std::logic_error {
  using std::logic_error::logic_error;
  ParseError() = delete;
};

class UnexpectedTokenException : public ParseError {
public:
  template <typename ... Args>
  UnexpectedTokenException(Token token, std::string lex, Token expected) : ParseError(
      "Unexpected token: " +
      std::to_string(token) +
      " (\"" + lex + "\"). Expected: " + std::to_string(expected)
  ) {};

  UnexpectedTokenException(Token token, std::string lex, std::string msg) : ParseError(
      "Unexpected token: " +
      std::to_string(token) +
      " (\"" + lex + "\"). " + msg
  ) {};

};




class Parser {
public:

  typedef std::unique_ptr<Tree> Node;

  static Node Parse(std::istream& is) {
    return Parser(is).parse();
  }

  static Node Parse(std::string str) {
    std::istringstream is(str);
    return Parser(is).parse();
  }


  Parser(std::istream& is) : lexer_(is) {
  }

  Node parse() {
    return S();
  }

private:
  Lexer lexer_;


  Token Expect(Token token) {
    if(lexer_.current_token() != token) {
      throw UnexpectedTokenException(lexer_.current_token(), lexer_.current_lex(), token);
    }
    return lexer_.current_token();
  }

  Token Consume(Token token) {
    if(lexer_.current_token() != token) {
      throw UnexpectedTokenException(lexer_.current_token(), lexer_.current_lex(), token);
    }
    lexer_.NextToken();
    return token;
  }


  Node S() {
    Node node(new Tree("S"));
    node->EmplaceChild(Consume(Token::VAR));
    node->AddChild(L());
    Expect(Token::END);
    return node;
  }

  Node L() {
    Node node(new Tree("L"));
    node->AddChild(P());
    switch (lexer_.current_token()) {
      case Token::NAME :
        node->AddChild(L());
        return node;
      case Token::END:
        return node;
      default: throw UnexpectedTokenException(lexer_.current_token(), lexer_.current_lex(), "Expected NAME or END");
    }
  }

  Node P() {
    Node node(new Tree("P"));
    node->AddChild(N());
    node->EmplaceChild(Consume(Token::COLON));
    Expect(Token::TYPE);
    node->EmplaceChild(lexer_.current_token(), lexer_.current_lex());
    lexer_.NextToken();
    node->EmplaceChild(Consume(Token::SEMICOLON));
    return node;

  }

  Node N() {
    Node node(new Tree("N"));
    switch (lexer_.current_token()) {
      case Token::NAME :
        node->EmplaceChild(lexer_.current_token(), lexer_.current_lex());
        switch (lexer_.NextToken()) {
          case Token::COMMA :
            node->EmplaceChild(Consume(Token::COMMA));
            node->AddChild(N());
            return node;
          case Token::COLON:
            return node;
          default: throw UnexpectedTokenException(
                lexer_.current_token(),
                lexer_.current_lex() ,
                "Expected: " + std::to_string(Token::NAME) + " or " + std::to_string(Token::COLON)
            );
        }
      default: throw UnexpectedTokenException(lexer_.current_token(), lexer_.current_lex(), Token::NAME);
    }


  }


};

#endif //LP_LAB1_PARSER_H
