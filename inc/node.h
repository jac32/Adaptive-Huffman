#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

#include <memory>
#include <iostream>

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
  bool is_internal() { return left != nullptr && right != nullptr ; }
  bool is_left_child();
  void update_weight();

  // Accessors
  Node* get_group_next();
  Node* get_group_prev();
  Node* get_parent() { return parent; }
  char get_symbol() { return symbol; }
  Node* get_left() { return left.get(); }
  int get_weight() { return weight; }

  // Mutators
  void set_group_next(Node* next) { group_next = next; };
  void set_group_prev(Node* prev) { group_prev = prev; };
  void set_parent(Node* parent) { this->parent = parent; }


  void set_weight(int weight) { this->weight = weight; }

  void release_left() { left.release(); }
  void set_left(Node* new_left) {
    left = std::unique_ptr<Node>(new_left); left->set_parent(this);
  }

};

#endif // HUFFMAN_NODE_H_
