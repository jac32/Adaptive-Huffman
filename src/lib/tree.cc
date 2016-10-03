#include <set>
#include <iostream>

#include "tree.h"


Tree::Tree(std::ostream& output) : output(output) {
  this->root = std::unique_ptr<Node>(new Node());
  this->nyt = this->root.get();
}

void Tree::process_symbol(char symbol) {
  Node* leaf;

  // This is a symbol Not Yet Transmitted
  if(!contains(symbol)) {
	// Raw symbols preceded by NYT path
	this->nyt->transmit_path(this->output);

	output.push_byte(symbol);
	
    leaf = new Node(symbol);

    // Split the NYT Node into a NYT and a new leaf
    // and set new root when transmitting the first symbol
    if (nyt == get_root()) {
	  this->set_root(new Node(nyt, leaf));
    }
	else {
      nyt->get_parent()->set_left(new Node(nyt, leaf));
    }
    // Add the leaf Node to the symbol map
    leaves[symbol] = leaf;
  }
  else {
	// This symbol has been seen before, so we can
	// update the corresponding leaf node
    leaf = leaves[symbol];

	std::cout << "Begin transmitting " << symbol << "..." << std::endl;
	leaf->transmit_path(this->output);
	std::cout << "Done transmitting " << symbol << "..." << std::endl;
	std::cout << std::endl;
  }

  // Since the leaf's weight has changed, parent weights and
  // weight groups will need updated.
  while (leaf->get_parent() != nullptr) {
    if (leaf->get_weight() > 0) perform_swap(leaf);
    update_weight(leaf);
    leaf = leaf->get_parent();
  }
}

// Expects weight > 0
void Tree::perform_swap(Node* lower) {
  int weight_class = lower->get_weight();

  // The head of the list is the highest ordering
  Node* upper = groups[weight_class];

  // If the lower Node is the head then no swap will be valid.
  if (upper == nullptr || upper == lower) { return; }

  // TODO: why is upper nullptr? 
  Node* upper_parent = upper->get_parent();
  Node* lower_parent = lower->get_parent();

  bool upper_is_left_child = upper_parent->get_left() == upper;
  bool lower_is_left_child = lower_parent->get_left() == lower;
  
  upper_is_left_child ? upper_parent->set_left(lower) : upper_parent->set_right(lower);
  lower_is_left_child ? lower_parent->set_left(upper) : lower_parent->set_right(upper);

  groups[weight_class] = lower;

  
  // TODO: This might be quicker if the data for the two nodes were swapped
  // Would likely involve extensive rewrite and benchmarking, seems premature.

  // BEGIN: Group swap from http://ptspts.blogspot.co.uk/2010/01/how-to-swap-two-nodes-in-doubly-linked.html
  Node* temp;
  
  temp = lower->get_group_next();
  lower->set_group_next(upper->get_group_next());
  upper->set_group_next(temp);
  lower->get_group_next()->set_group_next(lower);
  upper->get_group_next()->set_group_next(upper);

  temp = lower->get_group_prev();
  lower->set_group_prev(upper->get_group_prev());
  upper->set_group_prev(temp);
  lower->get_group_prev()->set_group_next(lower);
  upper->get_group_prev()->set_group_next(upper);
  // END: Group swap from http://ptspts.blogspot.co.uk/2010/01/how-to-swap-two-nodes-in-doubly-linked.html
}

void Tree::update_weight(Node* update_node) {
  if (update_node->get_left() == nullptr && update_node->get_left() == nullptr){
    change_weight(update_node, update_node->get_weight() + 1);
  }
  else { 
    int left_weight = update_node->get_left()->get_weight();
    int right_weight = update_node->get_right()->get_weight();
    change_weight(update_node, left_weight + right_weight);
  }
}

void Tree::change_weight(Node* changed, int new_weight) {

  Node* current_next = changed->get_group_next();
  Node* current_prev = changed->get_group_prev();

  int current_weight = changed->get_weight();

  bool is_head = groups[current_weight] == changed;
  bool is_only = current_next == changed;


  // Update old group mapping
  if (is_head && is_only) {
    groups.erase(current_weight);
  }
  else if (is_head) {
    groups[current_weight] = current_next;
  }

  // Update current neighbors to point to each other
  // (i.e. linked list deletion)
  current_next->set_group_prev(current_prev);
  current_prev->set_group_next(current_next);

  // Update new group pointers

  // Group already exists
  if (groups.count(new_weight)) {
    Node* new_next = groups[new_weight];
    Node* new_prev = groups[new_weight]->get_group_prev();

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

Node* Tree::get_root() { return root.get(); } 
Node* Tree::get_weight_group(int weight) { return groups[weight]; }

void Tree::set_root(Node* root) {
	this->root.release();
	this->root = std::unique_ptr<Node>(root);
}
