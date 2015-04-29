//
// Created by  Vladimir Skipor on 29/04/15.
//

#ifndef LP_LAB1_TREE_H
#define LP_LAB1_TREE_H

#include "Token.h"
#include <vector>
#include <memory>


class Tree {
public:

  typedef std::unique_ptr<Tree> Child;

  Tree(Token token) : token_(token) { };

  Tree(Token token, std::string lex) : token_(token), lex_(std::move(lex)) {
  };

  template<typename ... Children>
  Tree(Token token, Child&& ch, Children&& ...  children) : token_(token) {
    AddChildren(std::forward<Child>(ch), std::forward<Children>(children)...);
  };

  template<typename ... Children>
  Tree(Token token, Tree* ch, Children&& ...  children) : token_(token) {
    AddChildren(ch, std::forward<Children>(children)...);
  };

  Tree(const Tree&) = default;

  Tree(Tree&&) = default;


  void AddChild(Child&& child) {
    children_.emplace_back(std::forward<Child>(child));
  }

  void AddChild(Tree* child) {
    AddChild(Child(child));
  }

  template<typename ChildT, typename ... Children>
  void AddChildren(ChildT&& ch, Children&& ...  children) {
    AddChild(std::forward<ChildT>(ch));
    AddChildren(std::forward<Children>(children)...);
  };


private:
  Token token_;
  std::string lex_;
  std::vector<Child> children_;

  void AddChildren() { };

  void PrintToStream(std::ostream& os, size_t depth) const {
    std::string line_prefix;
    line_prefix.append(depth * 2, ' ');

    os << line_prefix;
    os << "<" << std::to_string(token_);
    if (!lex_.empty()) {
      os << ": " << lex_;
    }
    for (const auto & ch : children_) {
      os << '\n';
      ch->PrintToStream(os, depth + 1);
    }
    if(children_.empty()) {
      os << ">";
    } else {
      os << "\n" << line_prefix << ">";
    }

  }

  friend std::ostream & operator<<(std::ostream& os, Tree const&);

};

std::ostream & operator<<(std::ostream& os, const Tree& t) {
  t.PrintToStream(os, 0);
  return os;
};

namespace std {
  string to_string(Tree const& t) {
    std::stringstream s;
    s << t;
    return s.str();
  };
}
#endif //LP_LAB1_TREE_H
