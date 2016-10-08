#include <iostream>
#include <fstream>
#include <sstream>

#include <unistd.h>

#include "Flags.hh"
#include "tree.h"


int main (int argc, char* argv[]) {
  // Initialize input, output and data structure
 
  Tree tree(std::cin, std::cout);

  Flags flags;
  bool encode, decode, help;

  flags.Bool(encode, 'e', "encode", "encode the input stream");
  flags.Bool(decode, 'd', "decode", "decode the input stream");
  flags.Bool(help, 'h', "help", "show this help and exit");

  if (!flags.Parse(argc, argv)) {
    flags.PrintHelp(argv[0]);
    return 1;
  }
  else if (encode && decode) {
	std::cout << "only one of encode and decode can be set" << std::endl;
	flags.PrintHelp(argv[0]);
	return 1;
  }
  else if (help) {
    flags.PrintHelp(argv[0]);
    return 0;
  }
  else if (encode) {
	tree.encode();
  }
  else if (decode) {
	tree.decode();
  }
  else {
	flags.PrintHelp(argv[0]);
  }

  return 0;
}
