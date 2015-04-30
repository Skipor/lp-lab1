//
// Created by  Vladimir Skipor on 30/04/15.
//
#include <gtest/gtest.h>
#include <iostream>
#include "Parser.h"

using namespace std;

TEST(NoFailureParse, Rand1) {
  ASSERT_NO_THROW(Parser::Parse("var chara, int, \n astringc:integer; string_, var_, g,d,D, L_D_x_  \n  :      char;"));
}

TEST(NoFailureParse, AllTypesTest) {
  ASSERT_NO_THROW(Parser::Parse("var abcde_efGk : integer;"));
  ASSERT_NO_THROW(Parser::Parse("var abcde_efGk : char;"));
  ASSERT_NO_THROW(Parser::Parse("var abcde_efGk : real;"));
  ASSERT_NO_THROW(Parser::Parse("var abcde_efGk : boolean;"));
  ASSERT_NO_THROW(Parser::Parse("var abcde_efGk : string;"));
}


TEST(CorrectParceTest, NnRuleTest) { //N->n rule test
  cout << *Parser::Parse("var a : integer;") << endl;

  ASSERT_EQ(*Parser::Parse("var a : integer;"),
            *Parser::Node(
                new Tree("S",
                         new Tree(Token::VAR),
                         new Tree("L",
                                  new Tree("P",
                                           new Tree("N",
                                                    new Tree(Token::NAME, "a")
                                           ),
                                           new Tree(Token::COLON),
                                           new Tree(Token::TYPE, "integer"),
                                           new Tree(Token::SEMICOLON)
                                  )

                         )
                )
            )

  );

}

TEST(CorrectParceTest, NnNruleTest) { // N->n,N ; L->P rules test
  cout << *Parser::Parse("var a , b : integer;") << endl;

  ASSERT_EQ(*Parser::Parse("var a , b: integer;"),
            *Parser::Node(
                new Tree("S",
                         new Tree(Token::VAR),
                         new Tree("L",
                                  new Tree("P",
                                           new Tree("N",
                                                    new Tree(Token::NAME, "a"),
                                                    new Tree(Token::COMMA),
                                                    new Tree("N",
                                                             new Tree(Token::NAME, "b")
                                                    )

                                           ),
                                           new Tree(Token::COLON),
                                           new Tree(Token::TYPE, "integer"),
                                           new Tree(Token::SEMICOLON)
                                  )

                         )
                )
            )

  );


}
//
//TEST(CorrectParceTest, LPLruleTest) { // L -> PL
//  cout << *Parser::Parse("var a , b : integer; c , d : real;") << endl;
//
//  ASSERT_EQ(*Parser::Parse("var a , b : integer; c , d : real;"),
//            *Parser::Node(
//                new Tree("S",
//                         new Tree(Token::VAR),
//                         new Tree("L",
//                                  new Tree("P",
//                                           new Tree("N",
//                                                    new Tree(Token::NAME, "a"),
//                                                    new Tree(Token::COMMA),
//                                                    new Tree("N",
//                                                             new Tree(Token::NAME, "b")
//                                                    )
//
//                                           ),
//                                           new Tree(Token::COLON),
//                                           new Tree(Token::TYPE, "integer"),
//                                           new Tree(Token::SEMICOLON)
//                                  )
//
//                         )
//                )
//            )
//
//  );
//}

