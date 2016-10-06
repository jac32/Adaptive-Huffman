#include <set>
#include <string>
#include <iostream>
#include <fstream>

#include "tree.h"

Tree::Tree(std::istream& input, std::ostream& output) : input(input), output(output) {
  root = std::unique_ptr<Node>(new Node());
  nyt = this->root.get();
}

void Tree::encode() {
  OutputBuffer output_buffer(output);
  char input_byte = input.get();

  // Encode stream
  while (!input.eof()) {
	process_symbol(input_byte, output_buffer);
	input_byte = input.get();
  }

  // Provide non-ambiguous padding
  
  if (!output_buffer.empty()) {
	nyt->transmit_path(output_buffer);
	output_buffer.flush(true);
  }
}


void Tree::decode() {
  InputBuffer input_buffer(input); 

  // TEMP WHILE FIGURING OUT API
  std::ofstream noop_stream ("/dev/null");
  OutputBuffer noop_buffer(noop_stream); 

  char symbol;
  bool go_right;
  Node* ptr = root.get();
  while (!input_buffer.empty()) {
	if (!ptr->is_leaf()) {
	  go_right = input_buffer.receive_bit();
	  ptr = ptr->next(go_right);
	}
	else {
	  if (ptr == nyt) {
		if (input.eof()) return;
		symbol = input_buffer.receive_byte();
	  }
	  else {
		// At leaf so use symbol and reset ptr
		symbol = ptr->symbol;
	  }
	  output << symbol;
	  process_symbol(symbol, noop_buffer);
	  ptr = root.get();
	}
  }
}

void Tree::process_symbol(char symbol, OutputBuffer& buffer) {
  Node* leaf;

  // This is a symbol Not Yet Transmitted
  if(!contains(symbol)) {
	// Raw symbols preceded by NYT path
	nyt->transmit_path(buffer);
	buffer.send_byte(symbol);
    leaf = new Node(symbol);

    // Split the NYT Node into a NYT and a new leaf
    // and set new root when transmitting the first symbol
    if (nyt == get_root()) {
	  set_root(new Node(nyt, leaf));
    }
	else {
      nyt->parent->set_left(new Node(nyt, leaf));
    }
    // Add the leaf Node to the symbol map
    leaves[symbol] = leaf;
  }
  else {
	// This symbol has been seen before, so we can
	// update the corresponding leaf node
    leaf = leaves[symbol];
	leaf->transmit_path(buffer);
  }

  // Since the leaf's weight has changed, parent weights and
  // weight groups will need updated.
  while (leaf->parent != nullptr) {
    if (leaf->weight > 0) perform_swap(leaf);
    update_weight(leaf);
    leaf = leaf->parent;
  }
}

// Expects weight > 0
void Tree::perform_swap(Node* lower) {
  int weight_class = lower->weight;

  // The head of the list is the highest ordering
  Node* upper = groups[weight_class];

  // If the lower Node is the head then no swap will be valid.
  if (upper == nullptr || upper == lower) { return; }

  // TODO: why is upper nullptr? 
  Node* upper_parent = upper->parent;
  Node* lower_parent = lower->parent;

  bool upper_is_left_child = upper_parent->left.get() == upper;
  bool lower_is_left_child = lower_parent->left.get() == lower;
  
  upper_is_left_child ? upper_parent->set_left(lower) : upper_parent->set_right(lower);
  lower_is_left_child ? lower_parent->set_left(upper) : lower_parent->set_right(upper);

  // Swap head pointer
  groups[weight_class] = lower;
  
  // TODO: This might be quicker if the data for the two nodes were swapped
  // Would likely involve extensive rewrite and benchmarking, seems premature.

  // BEGIN: Group swap from http://ptspts.blogspot.co.uk/2010/01/how-to-swap-two-nodes-in-doubly-linked.html
  Node* temp;
  
  temp = lower->group_next;
  lower->group_next = upper->group_next;
  upper->group_next = temp;
  lower->group_next->group_prev = lower;
  upper->group_next->group_prev = upper;

  temp = lower->group_prev;
  lower->group_prev = upper->group_prev;
  upper->group_prev = temp;
  lower->group_prev->group_next = lower;
  upper->group_prev->group_next = upper;
  // END: Group swap from http://ptspts.blogspot.co.uk/2010/01/how-to-swap-two-nodes-in-doubly-linked.html
}

void Tree::update_weight(Node* update_node) {
  if (update_node->left == nullptr && update_node->left == nullptr){
    change_weight(update_node, update_node->weight + 1);
  }
  else { 
    int left_weight = update_node->left->weight;
    int right_weight = update_node->right->weight;
    change_weight(update_node, left_weight + right_weight);
  }
}

void Tree::change_weight(Node* changed, int new_weight) {
  Node* current_next = changed->group_next;
  Node* current_prev = changed->group_prev;

  int current_weight = changed->weight;

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
  current_next->group_prev = current_prev;
  current_prev->group_next = current_next;

  // Update new group pointers

  // Group already exists
  if (groups.count(new_weight)) {
    Node* new_next = groups[new_weight];
    Node* new_prev = groups[new_weight]->group_prev;

    new_prev->group_next = changed;
    new_next->group_prev = changed;

    changed->group_prev = new_prev;
    changed->group_next = new_next;
  }
  // Create a new group with the changed node as head
  else {
    groups[new_weight] = changed;
    changed->group_prev = changed;
    changed->group_next = changed;
  }

  // Actually set the node's weight
  changed->weight = new_weight;
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
