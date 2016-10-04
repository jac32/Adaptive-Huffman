#include <iostream>
#include <fstream>
#include <sstream>

#include "tree.h"

int main () {
  // Initialize input, output and data structure
  std::fstream input ("compressed.huff", std::fstream::in);
  //std::fstream output ("compressed.huff", std::fstream::in | std::fstream::out);

  Tree t(input, std::cout);

  t.decode();

  // Cleanup
  input.close();
  output.close();
}
