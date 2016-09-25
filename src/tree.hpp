#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_


#include <iostream>

#include "node.hpp"

class Tree {
  Node* root;
  Node* zero;
  std::istream &input;
  std::ostream &output;
public:
  Tree(std::istream&, std::ostream&);
  ~Tree();
  void update(char);
  void encode();
  void decode();
  bool contains(char);
  Node* get_zero();
};


#endif // HUFFMAN_TREE_H_
