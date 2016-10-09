
Adaptive Huffman CS3302-DE                                           {#mainpage}
===========================

**Author:** 140013444

**Marker:** Tom Kelsey

**Date:** 7th October 2016

Quick Start
-----
``` sh
	$ echo -n "hello world" | ./huff -e | ./huff -d
	>> hello world
```
 
Specification
-------------
This application was written as a solution for Practical 1 of module CS3302-DE at the University of St Andrews.
The stated purpose of the pratical was to gain experience with a widely used compression algorithm.

The specification was as follows:

- Implement an Adaptive Huffman encoder (persistant tree is optional)
- Implement an Adaptive Huffman decoder (decoder optional)

Choosing not to implement any of the optional parts of the specification would limit the maximum grade to a 16.
Choosing not to implement both optional parts of the specification would limit the maximum grade to a 13.

It was specified that any reasonable adaptive algorithm could be implemented.

It was also stated that the preferred implementation language was Java and that C++, C and Python are also acceptable.

Architecture
------------

### Project Directory Structure

```
.
├── CMakeLists.txt
├── Doxyfile.in
├── README.md
├── ext
│   └── gtest
├── inc
│   ├── Flags.hh
│   ├── buffer.h
│   ├── node.h
│   └── tree.h
├── src
│   ├── lib
│   └── main.cc
└── test
    ├── buffer_test.cc
    └── tree_test.cc
```

Top level overview: 

- `CMakeLists.txt` defines the build process for the project.
- `Doxyfile.in` contains the configuration for the automatic documentation generation.
- `ext/` contains external library files
- `inc/` contains project header files
- `src/` contains project src files (binaries and executables)
- `test/` contains test files 

File naming conventions are as follows:
- Internal header files use '.h' extension
- Internal source files use '.cc' extension
- Data structure unit tests use structure header name with '_test' postfix


### Tooling Overview
Although the preferred language was Java, C++ was chosen for several reasons. 
These are listed in approximately descending order of priority:

**Personal Growth:**
JH Team Project was democratically decided to be written in C++. 
As I have never previously had the opportunity to learn the language, this project seemed ideal for gaining some foundational experience.

**Simplicity:**
Reading and writing to binary files and streams is abstracted over in the Java standard library. 
While this is useful for most purposes, productive use of these abstractions requires a familiarity with the standard library that I do not currently possess. 
C++, however, uses C primitives with which I have had previous experience.

**Performance:**
C++ is generally a more performant langauge and should therefore allow for faster compression speeds.

**Tooling**
Thanks to JH project preparation, I have become familiar with the wide variety of high quality C++ tools available.

A brief summary of tools used follows:

- **Build Tool:** CMake
- **Testing:** GoogleTest
- **Continuous Integration:** Travis CI
- **Documentation:** Doxygen


### Algorithm

This Adaptive Huffman encoding is a variant of the FGK algorithm (Knuth 1985).

The key data structure is a dynamic representation of the code tree with `encode` and `decode` functions that are defined as follows:

``` 
	fn encode_symbol(): 
		x := read_symbol()
		if tree_ontains(x):
			output(x)
			Tree.acknowledge(x)	
		else: 
			output(path_of(NYT))
			output(path_of(x))
```

``` 
	fn decode_symbol():
		n := root
		while !leaf(n):
			n := step(receive_bit())

		if is_nyt(n):
			symbol := receive_byte()
		else:
			symbol:= symbol_of(n)
			
		output(symbol)
		Tree.acknowledge(symbol)
```

The Tree is a binary tree structure with the following invariant:

	All nodes can be listed in order of non-increasing weight with each node adjacent to its sibling.
	
Before updating node weights, it is checked if any node exists with the same weight higher up in the tree.
If such a node exists, the current node is swapped with the highest && right-most node with the same weight.
This means that the invariant is enforced and results in the heavier weighted nodes appearing higher in the tree.

From the `encode` and `decode` functions, we can see the data structure be dynamically maintained through the use of the `Tree.acknowledge()` which is defined here:

```
	fn Tree.acknowledge(symbol):
		if Tree.contains(symbol):
			// output is noop when decoding
			output_path_to(leaf_wtih(symbol))
		else:
			output_path_to(nyt)
			output(symbol)
			split_nyt(symbol)
			
		node := leaf_with(symbol)

		while node != root:
			perform_swap()
			increment weight of node
			node := parent(node)
```







Usage Instructions
-----

### Building

The project uses cmake to handle the build process. 
As is standard when using cmake, the following command will build the project:

``` sh 
	$ mkdir build && cd build && cmake .. && make 
``` 

To cleanly remove the newly built project, simply delete the `build/` directory.

``` sh
	$ rm -rf build/
```

The generated makefile will contain specific targets for building only the tests, the project library or the `huff` binary executable.

### Tests

The unit tests will be built automatically as part of the build process.
To run the tests, run the following command within the `build/` directory:

``` sh 
	$ ctest -VV
```

### Usage
 
The main executable can provide its own usage instructions:

``` sh
	$ huff --help
```

Testing
-------

Asserts are used to check the data structure invariants are maintained across operations.

Additionally, the basic buffer behaviour is unit tested.



- TODO: End to end tests on files


Evaluation
----------
 
 
 

References 
----------
[FGK Description (and psuedocode)](http://www.stringology.org/DataCompression/fgk/index_en.html)
[Vitter's paper on Dynamic Huffman Codes (Vitter 1989)](http://www.ittc.ku.edu/~jsv/Papers/Vit89.algojournalACMversion.pdf)
