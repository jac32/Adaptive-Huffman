
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

Report is auto-generated from this README and from code documentation.
Tools allocate `Chapter 1` as main report all else is listing of library classes etc.
 
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

### Implementation Approach

 The algorithm is specifically dynamic and should process each symbol only once.
 For this style of task, `iostream`s are well suited.
 
 Additionally, the wide range of unix tools (e.g. cat, echo, head, tail, xxd) provide utilities for inspecting and managing these types of streams on the command line. 
 With this in mind, and the focus of the practical being on the algorithm and not the UI, a simple CLI was chosen.
 Any data stream can be piped into the program via `stdin` and the output simply dumps to `stdout`. 
 To allow for the possibility of more elegant interfaces (and in the spirit of modular software design) the data structure is implemented as a standalone library and builds as such.
 
 See the Usage section for more information.

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



The C++ implementation of this algorithm stays fairly true to the psuedocode displayed here, though there are a few other considerations.

- Leaf node lookup
- Highest node in weight group lookup 
- Symbol length

The lookup operations can be (and have been in this implementation) implemented in amortized constant time.

The approach for each lookup is independent.

#### Leaf Lookup

As each leaf is uniquely identified by its symbol, a mapping of symbols to leaf node pointers is simply maintained.
All this requires is an insertion into the map whenever a new symbol is seen and then leaf lookup and the contains operation are both constant time map indexing.

It is worth noting here that the standard `map` object in C++'s standard library does not offer the performance profile described here. 
Instead it is ordered and the `unordered_map` object is required. 
This was discovered while profiling performance post-development and was luckily a simple fix.
The performance increase was noticable for larger files but as the speed of compression was secondary to the compression rate in this pratical further performance profiling was not done.


#### Highest Common-Weighted Node Lookup

Performing ths lookup in constant time was slightly more interesting than simply including a mapping.

A doubly-linked circular list of nodes is used to define a weight class - with the head of the list being the highest (and right-most) in the tree.

Whenever a new node is added to the group (via a weight increment, tree insertion, etc.) it is placed to the rear of the list (constant time operation) and then, provided tree swaps also swap in the list, the order of nodes within the group is maintained.

With a mapping of weights to the heads of the corresponding lists, we can achieve constant time lookup for this operation.


#### Symbol Length
The current implementation supports only symbols of one byte in size.
A change in symbol length may provide several changes in performance:

For example, an increase in symbol length would:
- Increase the maximum tree size (capitalizing on the lookup optimizations)
- Possibly better capture the information in certain encodings (such as UTF-16)


Evaluation
----------

While the FGK variant was implemented due to prevalance in literature and of well documented implementations, other options were explored.

The strongest alternative was was proposed by Vitter.
The data structure is very similar to FGK with subtle changes to the invariant: 

	For each weight w, all leaves of weight w precede (in the implicit numbering) all internal nodes of weight w.   [Vitter 1987]

The implicit numbering is similar to the concept of order in FGK:
The bottom-left node has the lowest numbering and it increases as we move up the tree.

The algorithm has a similar compression rate in the average case but is resilient against FGK's pathological case.

 
Both of these algorithms are extremely sensitive to errors.
If a single bit is corrupted within the stream, the encoding of all following bits will be shifted resultingly.
Several approaches can be employed to combat this, including segmentation of the data stream.
This does however present challenges, as the tree has to be rebuilt for every new segment of the stream.

If a sufficiently dynamic tree was designed, such that the segmentation approach was feasible, then the resulting coding would be far more adaptive and would profit from clustering of symbols and similar phenomena that occur in certain information streams.

With more time this area be highly interesting to investigate further.





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

but examples of compression and decompression are shown below

#### Encoding
``` sh
	$ cat input.txt | huff -e > compressed.txt
```


#### Decoding
``` sh
	$ cat compressed.txt | huff -d > decompressed.txt
```


Testing
-------

Asserts are used to check the data structure invariants are maintained across operations.
Additionally, various buffer structures and some simple end-to-end example uses are unit tested. 


References 
----------
[FGK Description (and psuedocode)](http://www.stringology.org/DataCompression/fgk/index_en.html)
[Vitter's paper on Dynamic Huffman Codes (Vitter 1989)](http://www.ittc.ku.edu/~jsv/Papers/Vit89.algojournalACMversion.pdf)
