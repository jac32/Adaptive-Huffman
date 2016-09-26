#include "node.hpp"

Node::Node(int w) {
  weight = w;
}

Empty::Empty() : Node(0) {}

Leaf::Leaf(char symbol) : Empty() {
  this->symbol = symbol;
}


Branch::Branch(Node* left, Node* right) :
  Node(left->get_weight() + right->get_weight())
{
  left->set_parent(this);
  right->set_parent(this);
  this->left = left;
  this->right = right;
}

Branch::~Branch() {
  delete left;
  delete right;
}


Node* Leaf::search_weights(int weight) {
  if (this->get_weight() == weight) {
    return this;
  } else {
    return nullptr;
  }
}

Node* Branch::search_weights(int weight) {
  Node* result = left->search_weights(weight);
  if (result) { return result; }
  else {
    return right->search_weights(weight);
  }
}

Node* Empty::inorder_next() {
  Node* next = this->get_parent();
  if (this == ((Branch*) next)->get_left()) {
    return next;
  } else {
    while (next == ((Branch*) next)->get_left()) {
      //TODO: Fix this: http://stackoverflow.com/questions/12684191/implementing-an-iterator-over-binary-or-arbitrary-tree-using-c-11
      // next = next->get_parent
    }
  }
}

Node* Branch::inorder_next() {
  return this->right->leftmost();
}
