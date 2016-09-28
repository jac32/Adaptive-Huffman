#include <set>

#include "tree.h"

// http://www.stringology.org/DataCompression/fgk/index_en.html


// CONSTRUCTORS & DESTRUCTORS --------------------------------------------------
Tree::Tree() {
  nyt = new Node();
  root = std::unique_ptr<Node>(nyt);
}

void Tree::count_symbol(char symbol) {
  if(!counts.count(symbol)) {
    std::unique_ptr<Node> owned_nyt;

    if (nyt->get_parent() == nullptr) {
      owned_nyt = std::move(root);
      auto branch = new Node(owned_nyt, symbol);
      root = std::unique_ptr<Node>(branch);

    } else {
      add_branch(nyt, symbol);
    }
  } else {
    
  }

  counts[symbol]++;
}


void add_branch(Node* nyt, char symbol) {
  Node* parent = nyt->get_parent();

  if (nyt->is_left_child()) {
    owned_nyt = nyt->parent()->take_left();
    Node* branch = std::unique_ptr<Node>(new Node(owned_nyt, symbol));
    parent->set_left(branch);
  } else {
    owned_nyt = nyt->parent()->take_right();
    Node* branch = std::unique_ptr<Node>(new Node(owned_nyt, symbol));
    parent->set_right(branch);
  }
}


bool Tree::contains(char symbol) {
  return counts.count(symbol);
}
