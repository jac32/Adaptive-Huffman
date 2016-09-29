#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

// #include <iostream>
#include <map>
#include<memory>

#include "node.h"

class Tree {
  std::unique_ptr<Node> root;
  Node* nyt;
  std::map<char, Node*> leaves;

public:
  Tree();
  void update_symbol(char);
  void add_node(char);
  bool contains(char);
};

#endif // HUFFMAN_TREE_H_
