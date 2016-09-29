#include "node.h"

// CONSTRUCTORS -----------------------------------------------------------------
Node::Node() : left(nullptr), right(nullptr) {
  this->weight = 0;
}

Node::Node(Node* nyt, char symbol) {
  this->left = std::unique_ptr<Node>(nyt);
  this->right = std::unique_ptr<Node>(new Node(symbol));
}

Node::Node(char symbol) {
  this->weight = 1;
  this->symbol = symbol;
}

// WARNING: will return false for orphan nodes
bool Node::is_left_child() {
  return parent->get_left() == this;
}
