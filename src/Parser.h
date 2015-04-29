//
// Created by  Vladimir Skipor on 29/04/15.
//

#ifndef LP_LAB1_PARSER_H
#define LP_LAB1_PARSER_H

#include "Lexer.h"
#include "Tree.h"



class Parser {

static Node Parse(std::istream & is) {
  return Parser(is).parse();
}

static Node Parse(std::string str) {
  std::istringstream is(str);
  return Parser(is).parse();
}

public:
  typedef std::unique_ptr<Tree> Node;

  Parser(std::istream & is) : lexer_(is) {
  }

  Node parse() {
    return S();
  }

private:
  Lexer lexer_;

  Node S() {
   lexer_.Consume(Token::VAR);
    Node node(new Tree(lexer_.current_token()));




  }

  Node L() {

  }

  Node P() {

  }

  Node N() {

  }




};

#endif //LP_LAB1_PARSER_H
