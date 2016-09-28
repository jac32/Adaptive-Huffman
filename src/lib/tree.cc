#include <set>

#include "tree.h"

// http://www.stringology.org/DataCompression/fgk/index_en.html


// CONSTRUCTORS & DESTRUCTORS --------------------------------------------------
Tree::Tree() : nodes() {
  nodes.push_back(Node());
  root = &nodes[0];
}


// Tree::Tree(std::istream &input, std::ostream &output) : input(input), output(output) {
//   root = zero = new Empty();
//   root->set_parent(new Marker(root));
// }

// Tree::~Tree() {
//   delete root;
// }

// void Tree::encode() {
//   char symbol;
//   // TODO: update needs to deal with existing symbols
//   while ((symbol = input.get()) != input.end) {
//     if (this->contains(symbol)) {
//       this->update(symbol);
//     } else {
//       std::cout << "NYT: " << symbol << std::endl;
//       this->update(symbol);
//     }
//   }
// }

// void Tree::decode() {
//   // TODO: Implement decode
// }

void Tree::update(char symbol) {
  this->counts.insert(symbol);
}
//   Node* current_node = new Branch(this->get_zero(), new Leaf(symbol));
//   Node* swappable;
//   while (current_node != root) {
//     if ((swappable = this->has_swappable(current_node)) != nullptr) {
//       this->swap(current_node, swappable);
//     }
//     current_node->inc_weight();
//     current_node = current_node->get_parent();
//   }
//   current_node->inc_weight();



// Node* Tree::has_swappable(Node* changed) {
//   Node* result = root->search_weights(changed->get_weight());
//   if (result != changed->get_parent()) {
//     return result;
//   } else {
//     return nullptr;
//   }
// }

bool Tree::contains(char symbol) {
  return this->counts.count(symbol);
}

// --------------------------------------------------------------------------------
// Iterator
// --------------------------------------------------------------------------------

// TreeIter::TreeIter(Tree tree) {
//   this->ptr = tree.root->leftmost();
// }

// TreeIter::TreeIter(const TreeIter& other) {
//   this->ptr = other.ptr;
// }

// TreeIter& TreeIter::operator=(const TreeIter& other) {
//   this->ptr = other.ptr;
//   return *this;
// }

// TreeIter& TreeIter::operator++() {
//   this->ptr = this->ptr->inorder_next(); 
//   return *this;
// }

// TreeIter::reference TreeIter::operator*() {
//   return ptr;
// }

// void swap(TreeIter &lhs, TreeIter &rhs) {
//   std::swap(lhs.ptr, rhs.ptr);
// }
