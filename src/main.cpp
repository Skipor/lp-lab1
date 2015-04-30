#include "Lexer.h"
#include "Tree.h"
#include "Parser.h"

#include <iostream>



using namespace std;

int main() {
  string input("var chara, int, \n astringc:integer; string_, var_, g,d,D, L_D_x_  \n  :      char;");
  string input1("var chara, int+e_gerb, \n ast --- ringc:integer; string_, var_, g,d,D, L_D_x_  \n  :      char;");
  auto stream = istringstream(input);


  Lexer lexer(stream);
  while (lexer.current_token() != Token::END) {
    cout << to_string(lexer.NextToken()) << "   " << lexer.current_lex() << endl;
  }

  try {

  Parser::Node node = Parser::Parse(input);
  cout << *node << endl;
  } catch (ParseError & e) {
    cout << e.what();
  }


  Tree tree(Token::NAME, "abc");
  Tree tree1(Token::NAME, std::make_unique<Tree>(Token::NAME));
  typedef std::unique_ptr<Tree> Child;
  tree.AddChild(new Tree(Token::SEMICOLON));
  tree.AddChildren(
      new Tree(Token::SEMICOLON),
      new Tree(Token::SEMICOLON,
        new Tree (Token::NAME, std::make_unique<Tree>(Token::NAME))
      ),
      Child(new Tree(Token::COLON)),
      new Tree(Token::SEMICOLON)
  );

  cout << endl << tree;


  return 0;
}