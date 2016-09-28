#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

// #include <iostream>
#include <memory>
#include <vector>
#include <set>

#include "node.h"

class Tree {
  Node* root;
  std::vector<Node> nodes;
  std::set<char> counts;

public:
  Tree();
  void update(char);
  bool contains(char);

};

#endif // HUFFMAN_TREE_H_
