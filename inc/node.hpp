#ifndef HUFFMAN_NODE_HPP_
#define HUFFMAN_NODE_HPP_

// Classes
class Node;
class Empty;
class Leaf;
class Branch;


class Node {
  int weight;
  Node* parent;
public: 
  Node(int);
  virtual ~Node() {};

  virtual Node* search_weights(int) = 0;
  virtual Node* leftmost() = 0;
  virtual Node* inorder_next() = 0;

  Branch* get_parent() { return ((Branch*) parent); }
  int get_weight() { return weight; }

  void set_parent(Node* parent) { this->parent = parent; }
  void inc_weight() { weight++; }
};

class Marker : public Node {
  Node* root; 
public: 
  Marker(Node*);
  Node* leftmost() { return root; }
};

class Empty : public Node {
public:
  Empty();
  Node* inorder_next();
  Node* leftmost() { return this; }
  Node* search_weights(int);
};


class Leaf: public Empty {
  char symbol;
public:
  Leaf(char);
};


class Branch: public Node {
  Node* left;
  Node* right;
  
public: 
  Branch(Node*, Node*);
  ~Branch();
  
  Node* inorder_next() override;
  Node* search_weights(int) override;
  Node* leftmost() override { return left->leftmost(); }

  Node* get_right() { return right; }
  Node* get_left() { return left; }
};

#endif // HUFFMAN_NODE_HPP_
