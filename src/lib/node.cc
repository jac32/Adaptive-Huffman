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

// Accessors
Node* Node::get_group_next() { return group_next; }
Node* Node::get_group_prev() { return group_prev; }
Node* Node::get_parent() { return parent; }
Node* Node::get_left() { return left.get(); }
Node* Node::get_right() { return right.get(); }

// Mutators
void Node::set_group_next(Node* next) { group_next = next; };
void Node::set_group_prev(Node* prev) { group_prev = prev; };
void Node::set_parent(Node* parent) { this->parent = parent; }
void Node::set_weight(int weight) { this->weight = weight; }

void Node::set_left(Node* new_left) {
  left.release(); 
  left = std::unique_ptr<Node>(new_left); left->set_parent(this);
}
void Node::set_right(Node* new_right) {
  right.release(); 
  right = std::unique_ptr<Node>(new_right); right->set_parent(this);
}

