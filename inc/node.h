#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

#include <memory>
#include <vector>

// Classes
class Node {
  bool weighted;
  char symbol;
  Node* parent;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
  
public:
  Node();
  Node(char);
  Node(std::unique_ptr<Node>, char);
  bool is_internal() { return left != nullptr && right != nullptr ; }
  bool is_left_child();

  Node* get_parent() { return parent; }
  char get_symbol() { return symbol; }
  Node* get_left() { return left.get(); }
  std::unique_ptr<Node> take_left() { return std::move(left); }
  std::unique_ptr<Node> take_right() { return std::move(right); }

  void set_left(std::unique_ptr<Node> new_left) { left = std::move(new_left); }
  void set_right(std::unique_ptr<Node> new_right) { right = std::move(new_right); }


};

#endif // HUFFMAN_NODE_H_
