#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_


#include <iostream>

#include "node.hpp"

class Tree {
  Node* root;
  Node* zero;
  std::istream &input;
  std::ostream &output;

  friend class TreeIter;

public:
  Tree(std::istream&, std::ostream&);
  ~Tree();
  void update(char);
  void encode();
  void decode();
  bool contains(char);
  Node* has_swappable(Node*);
  void swap(Node*, Node*);
  void update_codes();


  Node* get_zero();
};


// iterator class is parametrized by pointer type
class TreeIter : std::iterator<std::input_iterator_tag, Node*>
{
  Node* ptr;

public:
  TreeIter(Tree);
  TreeIter(const TreeIter&);
  ~TreeIter() = default;
  TreeIter& operator=(const TreeIter&);
  TreeIter& operator++(); //prefix increment
  reference operator*();
  friend void swap(TreeIter &lhs, TreeIter &rhs); //C++11 I think
};

#endif // HUFFMAN_TREE_H_
