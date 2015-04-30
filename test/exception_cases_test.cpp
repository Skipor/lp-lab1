//
// Created by  Vladimir Skipor on 30/04/15.
//
#include <gtest/gtest.h>
#include "Parser.h"

TEST(NoIdentifierTest, OnlyVarTest) {
  ASSERT_THROW(Parser::Parse("var "), UnexpectedTokenException);
}

TEST(NoIdentifierTest, NoVarTest) {
  ASSERT_THROW(Parser::Parse("a, b, c : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("vara, b, c : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("varr a, b, c : char;"), UnexpectedTokenException);
}

TEST(NoIdentifierTest, NoNameTest) {
  ASSERT_THROW(Parser::Parse("var : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var , b, c : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, , c : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, 123 , c : char;"), UnexpectedTokenException);
}

TEST(NoIdentifierTest, NoCommaTest) {
  ASSERT_THROW(Parser::Parse("var b c : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b c : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b. c : char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b; c : char;"), UnexpectedTokenException);
}

TEST(NoIdentifierTest, NoColonTest) {
  ASSERT_THROW(Parser::Parse("var a, b, c  char;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c [ char;"), UnexpectedTokenException);
}

TEST(NoIdentifierTest, NoSemicolonTest) {
  ASSERT_THROW(Parser::Parse("var a, b, c : char i, j, y : string;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c : char; i, j, y : string"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c : char"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c : char]"), UnexpectedTokenException);
}

TEST(NoIdentifierTest, NoTypeTest) {
  ASSERT_THROW(Parser::Parse("var a, b, c : ;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c :"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c : var ;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c : xxx;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c : ; i, j, y : string;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, b, c : char; i, j, y : ;"), UnexpectedTokenException);
}
TEST(NoIdentifierTest, KeyWordsInstreadVariablesTest) {
  ASSERT_THROW(Parser::Parse("var a, integer, c : string;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, char, c : string;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, string, c : string;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, real, c : string;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, boolean, c : string;"), UnexpectedTokenException);
  ASSERT_THROW(Parser::Parse("var a, var, c : string;"), UnexpectedTokenException);
}

TEST(NoIdentifierTest, TypeInstreadVarTest) {
  ASSERT_THROW(Parser::Parse("char a, integer, c : string;"), UnexpectedTokenException);
}
