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

  Tree(Token token) : lex_(std::to_string(token)) { };

  Tree(const std::string & lex) : lex_(lex) {
  }

  Tree(Token token, const std::string & lex) : Tree(token) {
    lex_ += ": ";
    lex_ += lex;
  };

  template<typename ... Children>
  Tree(Token token, Child&& ch, Children&& ...  children) : Tree(token) {
    AddChildren(std::forward<Child>(ch), std::forward<Children>(children)...);
  };

  template<typename ... Children>
  Tree(Token token, Tree* ch, Children&& ...  children) : Tree(token) {
    AddChildren(ch, std::forward<Children>(children)...);
  };

  template<typename ... Children>
  Tree(std::string token, Child&& ch, Children&& ...  children) : Tree(token) {
    AddChildren(std::forward<Child>(ch), std::forward<Children>(children)...);
  };

  template<typename ... Children>
  Tree(std::string token, Tree* ch, Children&& ...  children) : Tree(token) {
    AddChildren(ch, std::forward<Children>(children)...);
  };


  Tree(const Tree&) = default;

  Tree(Tree&&) = default;

  bool operator==(const Tree & other) const {
    if (lex_ != other.lex_)  {
      return false;
    }
    if(children_.size() != other.children_.size()) {
      return false;
    }

    for(auto it1 = children_.begin(), it2 = other.children_.begin(), end1 = children_.end();
        it1 != end1;
        ++it1, ++it2
        ){
      if(*(*it1) != *(*it2)) {
        return false;
      }
    }
    return true;

  }


  bool operator!=(const Tree & other) const {
    return !(*this == other);
  }

  template<typename ... Args>
  void EmplaceChild(Args && ... args) {
    children_.emplace_back(std::make_unique<Tree>(std::forward<Args>(args)...));
  }

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
//  Token token_;
  std::string lex_;
  std::vector<Child> children_;

  void AddChildren() { };

  void PrintToStream(std::ostream& os, size_t depth) const {
    std::string line_prefix;
    line_prefix.append(depth * 2, ' ');

    os << line_prefix;
//    os << "<" << std::to_string(token_);
//    if (!lex_.empty()) {
//      os << ": " << lex_;
//    }
    os << "<" << lex_;
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
