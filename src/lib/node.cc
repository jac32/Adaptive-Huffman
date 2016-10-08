#include <stack>
#include <assert.h>
#include <iostream>

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

  left->parent = this;
  right->parent = this;

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

void Node::transmit_path(OutputBuffer& output) {
  std::stack<bool> path;

  Node* child = this;

  while (child->parent != nullptr) {
	assert(child->group_next->weight == child->weight);
	path.push(child == child->parent->right.get());
	child = child->parent;
  }

  while (path.size() > 0) {
	output.send_bit(path.top());
	path.pop();
  }
}

void Node::set_left(Node* left) {
  this->left.release(); 
  this->left = std::unique_ptr<Node>(left);
  this->left->parent = this;
}
void Node::set_right(Node* right) {
  this->right.release(); 
  this->right = std::unique_ptr<Node>(right);
  this->right->parent = this;
}

bool Node::is_leaf() { return left == nullptr && right == nullptr; }
char Node::get_symbol() { return symbol; }
int Node::get_weight() { return weight; }
Node* Node::get_next(bool go_right) { return go_right ? right.get() : left.get(); }
