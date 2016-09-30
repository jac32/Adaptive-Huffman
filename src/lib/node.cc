#include <assert.h>

#include "node.h"

// CONSTRUCTORS -----------------------------------------------------------------
Node::Node() : left(nullptr), right(nullptr) {
  weight = 0;
  parent = nullptr;
}

Node::Node(Node* nyt, Node* leaf) {
  parent = nullptr;
  left = std::unique_ptr<Node>(nyt);
  right = std::unique_ptr<Node>(leaf);

  left->set_parent(this);
  right->set_parent(this);
  weight = left->get_weight() + right -> get_weight();
}

Node::Node(char symbol) {
  weight = 1;
  parent = nullptr;
  this->symbol = symbol;
}

// WARNING: will return false for orphan nodes
bool Node::is_left_child() {
  return parent->get_left() == this;
}
