#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

#include <memory>
#include <vector>

// Classes
class Node {
  int weight;
  char symbol;
  Node* parent;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
  
public:
  Node();
  Node(char);
  Node(Node*, char);
  bool is_internal() { return left != nullptr && right != nullptr ; }
  bool is_left_child();

  Node* get_parent() { return parent; }
  char get_symbol() { return symbol; }
  Node* get_left() { return left.get(); }
  void release_left() { left.release(); }
  void release_right() {right.release(); }

  void set_left(Node* new_left) { left = std::unique_ptr<Node>(new_left); }
  void set_right(Node* new_right) { right = std::unique_ptr<Node>(new_right); }
  void inc_weight(int increment = 1) { weight += increment; }
};

#endif // HUFFMAN_NODE_H_
