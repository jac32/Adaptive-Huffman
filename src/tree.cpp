#include "tree.hpp"


// CONSTRUCTORS & DESTRUCTORS --------------------------------------------------
Tree::Tree(std::istream &input, std::ostream &output) : input(input), output(output) {
  root = zero = new NYT();
}

Tree::~Tree() {
  delete root;
}

void Tree::encode() {
  char symbol;
  while ((symbol = input.get()) != input.end) {
    if (this->contains(symbol)) {
      std::cout << "NYT: " << symbol << std::endl;
      this->update(symbol);
    }
  }
}

void Tree::decode() {}
void Tree::update(char symbol) {
  Node* current_node = new Branch(this->get_zero(), new Leaf(symbol));
  while (current_node != root) {
    // TODO: revisit
    // http://www.stringology.org/DataCompression/fgk/index_en.html
  }
}
