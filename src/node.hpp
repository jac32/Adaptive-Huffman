#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

class Node {
  int weight;
public: 
  Node(int);
  virtual ~Node() = default;

  int get_weight() { return weight; }
};


class NYT : public Node {
public:
  NYT();
};


class Leaf: public Node {
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
};

#endif // HUFFMAN_NODE_H_
