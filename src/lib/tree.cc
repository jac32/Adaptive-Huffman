#include <set>

#include "tree.h"

// http://www.stringology.org/DataCompression/fgk/index_en.html


// CONSTRUCTORS & DESTRUCTORS --------------------------------------------------
Tree::Tree() {
  nyt = new Node();
  root = std::unique_ptr<Node>(nyt);
}

void Tree::update_symbol(char symbol) {
  // if(!contains(symbol)) {
  //   if (nyt == root.get()) {
  //     root.release();
  //     root = std::unique_ptr<Node>(new Node(nyt, symbol));
  //   } else {
  //     Node* parent = nyt->get_parent();

  //     if (nyt->is_left_child()) {
  //     	nyt->get_parent()->release_left();
  //     	parent->set_left(new Node(nyt, symbol));
  //     } else {
  //     	nyt->get_parent()->release_right();
  //     	parent->set_right(new Node(nyt, symbol));
  //     }
  //   }
  // } else {
  //   leaves[symbol]->inc_weight();
  //     // TODO: rebalance tree
  // }
}


bool Tree::contains(char symbol) {
  return leaves.count(symbol);
}
