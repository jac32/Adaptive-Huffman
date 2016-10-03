/// @file tree.h
/// @author 140013444 
/// @date 7 Oct 2016
/// @brief Main data structure for CS3302-DE Adaptive Huffman coding
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

#include "bitdump.h"
#include "node.h"

/// @brief Adaptive Huffman code tree
///
// TODO: class Tree detailed explanation
class Tree {

  // TODO: allow streaming input
  //  std::istream& input;

  BitDump output; ///< Buffered output stream
  Node* nyt;      ///< Maintained pointer to the NYT node

  std::unique_ptr<Node> root;   ///< Tree owns root to provide auto cleanup
  std::map<int, Node*> groups;  ///< Mapping from weight to heighest node of weight
  std::map<char, Node*> leaves; ///< Mapping from symbol to representing leaf

  void update_weight(Node*);      ///< Increment leaf weight or recalculate branch weight
  void change_weight(Node*, int); ///< Change node weight, while maintaining groups
  void perform_swap(Node*);       ///< Swap the node with the heighest weighted in group

  // Accessors
  Node* get_root();                    ///< Provides a ptr to the root node
  Node* get_weight_group(int weight);  ///< Provides a ptr to the head of the weight group

  // Mutators
  void set_root(Node* root);  ///< Takes ownership of the new node (releases old)

public:
  Tree(std::ostream&);            ///< Standard constructor
  bool contains(char);            ///< Has the tree previously encoded the given symbol
  void process_symbol(char);      ///< Encode a single symbol and update structure
 };
#endif // HUFFMAN_TREE_H_
