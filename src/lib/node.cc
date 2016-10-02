#include <assert.h>

#include "node.h"

// CONSTRUCTORS -----------------------------------------------------------------
Node::Node() : left(nullptr), right(nullptr) {
  weight = 0;
  parent = nullptr;

  group_next = this;
  group_prev = this;
}

Node::Node(Node* nyt, Node* leaf) {
  weight = 0;
  parent = nullptr;
  left = std::unique_ptr<Node>(nyt);
  right = std::unique_ptr<Node>(leaf);

  left->set_parent(this);
  right->set_parent(this);

  group_next = this;
  group_prev = this;
}

Node::Node(char symbol) {
  weight = 0;
  parent = nullptr;
  this->symbol = symbol;
  group_next = this;
  group_prev = this;
}

// TODO: Handle root case
void Node::transmit_path(BitDump& output) {
  Node* parent = this->parent;
  Node* child = this;
  while (parent != nullptr) {
	output.push((child == parent->get_left() ?  0 : 1));
	child = parent;
	parent = parent->get_parent();
  }
}

