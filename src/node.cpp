#include "node.hpp"

Node::Node(int w) {
  weight = w;
}

NYT::NYT() : Node(0) {}

Leaf::Leaf(char symbol) : Node(0) {
  this->symbol = symbol;
}


Branch::Branch(Node* left, Node* right) :
  Node(left->get_weight() + right->get_weight())
{
  this->left = left;
  this->right = right;
}

Branch::~Branch() {
  delete left;
  delete right;
}


