#ifndef HUFFMAN_NODE_HPP_
#define HUFFMAN_NODE_HPP_

class Node {
  int weight;
  Node* parent;
public: 
  Node(int);
  virtual ~Node() = default;

  virtual Node* search_weights(int);
  virtual Node* leftmost();
  virtual Node* inorder_next();

  Node* get_parent() { return parent; }
  int get_weight() { return weight; }

  void set_parent(Node* parent) { this->parent = parent; }
  void inc_weight() { weight++; }
};


class Empty : public Node {
public:
  Empty();
  Node* inorder_next();
  Node* leftmost() { return this; }
  Node* search_weights(int) { return nullptr; }
};


class Leaf: public Empty {
  char symbol;
public:
  Leaf(char);
  Node* search_weights(int);
};


class Branch: public Node {
  Node* left;
  Node* right;
  
public: 
  Branch(Node*, Node*);
  ~Branch();

  
  Node* inorder_next();
  Node* leftmost() { return left->leftmost(); }
  Node* search_weights(int);

  Node* get_right() { return right; }
  Node* get_left() { return left; }
};

#endif // HUFFMAN_NODE_HPP_
