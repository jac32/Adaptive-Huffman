#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

#include <memory>
#include <vector>

// Classes
class Node {
  int weight;
  char symbol;
  Node* left;
  Node* right;
  
public:
  Node();
  bool is_internal() { return left != nullptr && right != nullptr ; }
  char get_symbol() { return symbol; }
};

#endif // HUFFMAN_NODE_H_
