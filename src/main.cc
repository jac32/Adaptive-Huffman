#include <iostream>
#include <fstream>
#include <sstream>

#include <unistd.h>

#include "tree.h"

int main (int argc, char* argv[]) {
  // Initialize input, output and data structure
  
  std::fstream input("test.huff");
  Tree t(input, std::cout);
  t.decode();

  // Tree tree(std::cin, std::cout);

  // int c;
  // while((c =  getopt(argc, argv, "de")) != EOF) {
  // 	  switch (c) {
  // 		case 'd':
  // 		  tree.decode();
  // 		  std::cout << std::endl;
  // 		  break;
  // 		case 'e':
  // 		  tree.encode();
  // 		  break;
  //       }

  //   }


  

  // Cleanup
}
