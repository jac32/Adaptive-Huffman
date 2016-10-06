/// @file node.h
/// @author 140013444 
/// @date 7 Oct 2016
/// @brief Node class for CS3302-DE Adaptive Huffman coding
//
/// The tree performs adaptive Huffman encoding/decoding between the 
/// provided streams. 
// TODO: Discuss implementation design/details
///

#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

#include <memory>
#include <iostream>

#include "buffer.h"

//TODO: Is member encapsulation necessary when Tree is friend class?

// Classes
class Node {
  friend class Tree; ///< The tree structure manages and manipulates its nodes

  int weight;  ///< Num occurrences for the symbol (or sum of children for internal)
  char symbol; ///< The symbol represented by this leaf (unused for internals)

  Node* parent;      ///< Pointer to the node's parent
  Node* group_next;  ///< Pointer to the next node in weight group
  Node* group_prev;  ///< Pointer to the prev node in weight group
 
  std::unique_ptr<Node> left, right;  ///< Node owns its children
 
  Node();              ///< Constructor for NYT Node
  Node(char);          ///< Constructor for leaf Node
  Node(Node*, Node*);  ///< Constructor for branch Node


  void transmit_path(OutputBuffer&);
  void set_left(Node*);
  void set_right(Node*);

public:
  bool is_leaf() { return left == nullptr && right == nullptr; }
  char get_symbol() { return symbol; }
  int get_weight() { return weight; }
  Node* next(bool go_right) { return go_right ? right.get() : left.get(); }
};

#endif // HUFFMAN_NODE_H_
