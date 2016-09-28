#ifndef HUFFMAN_NODE_H_
#define HUFFMAN_NODE_H_

// Classes
class Branch;
class Empty;
class Leaf;
class Node;
class Weighted;

class Node {

};
class Marker : public Node {
  
};
class Weighted : public Node {
  
};
class Branch : public Weighted {
  
};
class Empty : public Weighted {
  
};
class Leaf : public Empty {
  
};


#endif // HUFFMAN_NODE_H_
