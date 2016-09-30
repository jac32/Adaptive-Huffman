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

  if(!contains(symbol)) {

    Node* leaf = new Node(symbol);

    if (nyt == get_root()) {
      root.release();
      root = std::unique_ptr<Node>(new Node(nyt, leaf));
    }

    else {
      Node* parent = nyt->get_parent();
      parent->release_left();
      parent->set_left(new Node(nyt, leaf));
    }

    leaves[symbol] = leaf;
  }

  else {
    // TODO: register weight change on increment
    leaves[symbol]->inc_weight();
  }

  Node* ptr = leaves[symbol].get_parent();


  // TODO: Check for swaps before updating weights

  while (ptr.get_parent() != nullptr) {
    update_weight(ptr);
    ptr = ptr->get_parent();
  }
}


void Tree::update_weight(Node* changed) {

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
