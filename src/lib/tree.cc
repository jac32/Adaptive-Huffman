#include <set>
#include <iostream>

#include "tree.h"

// http://www.stringology.org/DataCompression/fgk/index_en.html


// CONSTRUCTORS & DESTRUCTORS --------------------------------------------------
Tree::Tree() {
  nyt = new Node();
  root = std::unique_ptr<Node>(nyt);
}

void Tree::process_symbol(char symbol) {
  Node* leaf;

  // This is a symbol Not Yet Transmitted
  if(!contains(symbol)) {

    // Create a new zero-weighted leaf node
    leaf = new Node(symbol);

    // Runs when transmitting the first symbol
    if (nyt == get_root()) {
      // TODO: Is the release required by the unique_ptr?
      root.release();
      root = std::unique_ptr<Node>(new Node(nyt, leaf));
    }
    // Split the NYT Node into a NYT and a new leaf
    else {
      Node* parent = nyt->get_parent();
      parent->release_left();
      parent->set_left(new Node(nyt, leaf));
    }

    // Add the leaf Node to the symbol map
    leaves[symbol] = leaf;
  }
  // This symbol has been seen before, so we can
  // update the corresponding leaf node
  else {
    // TODO: register weight change on increment
    leaf = leaves[symbol];
  }

  // TODO: Check for swaps before updating weights

  while (leaf.get_parent() != nullptr) {
    perform_swap(leaf);
    update_weight(leaf);
    leaf = leaf->get_parent();
  }
}

void perform_swap() {
  
}


void Tree::change_weight(Node* changed, int new_weight) {

  Node* current_next = changed->get_group_next();
  Node* current_prev = changed->get_group_prev();

  int left_child_weight = changed->get_left()->get_weight() 
  int right_child_weight =  changed->get_right()->get_weight();

  int current_weight = changed->get_weight();
  int new_weight = left_child_weight + right_child_weight;

  bool is_head = groups[current_weight] == changed;
  bool is_only = current_next == changed;


  // Update old group mapping
  if (is_head && is_only) {
    groups.erase(current_weight);
  } else if (is_head) {
    groups[old_weight] = current_next;
  }

  // Update current neighbors to point to each other
  // (i.e. linked list deletion)
  current_next->set_prev(current_prev);
  current_prev->set_next(current_next);

  // Update new group pointers

  // Group already exists
  Node* group_head = groups[new_weight];
  if (group_head != groups.end()) {
    Node* new_next = group_head;
    Node* new_prev = group_head->get_group_prev();

    new_prev->set_group_next(changed);
    new_next->set_group_prev(changed);

    changed->set_group_prev(new_prev);
    changed->set_group_next(new_next);
  }
  // Create a new group with the changed node as head
  else {
    groups[new_weight] = changed;
    changed->set_group_prev(changed);
    changed->set_group_next(changed);
  }

  // Actually set the node's weight
  changed->set_weight(new_weight);
}


bool Tree::contains(char symbol) {
  return leaves.count(symbol);
}
