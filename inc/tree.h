/// @file tree.h
/// @author 140013444 
/// @date 7 Oct 2016
/// @brief Main Tree structure for CS3302-DE Adaptive Huffman coding
//
/// The tree performs adaptive Huffman encoding/decoding between the 
/// provided streams. 
// TODO: Discuss implementation design/details
// TODO: Add references:
///
/// @see Vitters paper
/// @see FGK paper
/// @see Studres Specification
///
#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <iostream>
#include <map>
#include <memory>

#include "buffer.h"
#include "node.h"

/// @brief Adaptive Huffman code tree
///
// TODO: class Tree detailed explanation
class Tree {

  std::istream& input; ///< Buffered input stream
  std::ostream& output; ///< Buffered output stream

  Node* nyt;      ///< Maintained pointer to the NYT node

  std::unique_ptr<Node> root;   ///< Tree owns root to provide auto cleanup
  std::map<int, Node*> groups;  ///< Mapping from weight to heighest node of weight
  std::map<char, Node*> leaves; ///< Mapping from symbol to representing leaf

  void update_weight(Node*);      ///< Increments leaf weight or recalculates branch weight
  void change_weight(Node*, int); ///< Changes node weight, while maintaining groups
  void perform_swap(Node*);       ///< Swaps the node with the heighest weighted in group

  // Accessors
  Node* get_root();                    ///< Provides a ptr to the root node
  Node* get_weight_group(int weight);  ///< Provides a ptr to the head of the weight group

  // Mutators
  void set_root(Node* root);  ///< Takes ownership of the new node (releases old)

public:
  Tree(std::istream&, std::ostream&);  ///< Standard constructor

  bool contains(char);  ///< Checks the tree for a given symbol

  void process_symbol(char, OutputBuffer&);  ///< Encodes a single symbol and update structure

  void encode();  ///< Begins encoding of the input stream
  void decode();  ///< Begins decoding of the input stream
 };

#endif // HUFFMAN_TREE_H_
