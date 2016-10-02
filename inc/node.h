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

#include "bitdump.h"

// Classes
class Node {
  int weight;
  char symbol;
  Node* parent;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
  Node* group_next;
  Node* group_prev;
  
public:
  Node();
  Node(char);
  Node(Node*, Node*);
  void transmit_path(BitDump&);

  bool is_leaf() { return left == nullptr && right == nullptr;}

  // Accessors
  Node* get_group_next() { return group_next; }
  Node* get_group_prev() { return group_prev; }
  Node* get_parent() { return parent; }
  char get_symbol() { return symbol; }
  Node* get_left() { return left.get(); }
  Node* get_right() { return right.get(); }
  int get_weight() { return weight; }

  // Mutators
  void set_group_next(Node* next) { group_next = next; };
  void set_group_prev(Node* prev) { group_prev = prev; };
  void set_parent(Node* parent) { this->parent = parent; }
  void set_weight(int weight) { this->weight = weight; }

  void set_left(Node* new_left) {
    left.release(); 
    left = std::unique_ptr<Node>(new_left); left->set_parent(this);
  }
  void set_right(Node* new_right) {
    right.release(); 
    right = std::unique_ptr<Node>(new_right); right->set_parent(this);
  }


};

#endif // HUFFMAN_NODE_H_
