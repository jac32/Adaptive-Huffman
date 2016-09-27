#include <iostream>

#include "tree.hpp"

int main () {
  std::cout << std::endl;

  Tree *t = new Tree(std::cin, std::cout);

  std::cout << "Hello, World!" << std::endl;

  delete t;
}
