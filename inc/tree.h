#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

// #include <iostream>
#include <map>
#include<memory>

#include "node.h"

class Tree {
  Node* nyt;
  std::unique_ptr<Node> root;
  std::map<int, Node*> groups;
  std::map<char, Node*> leaves;

public:
  Tree();
  void process_symbol(char);
  bool contains(char);
  int total_weight() { return root->get_weight(); }

  void update_weight(Node*);

  // Accessors
  Node* get_root() { return root.get(); };
  Node* get_weight_group(int weight) { return groups[weight]; }
};

#endif // HUFFMAN_TREE_H_
