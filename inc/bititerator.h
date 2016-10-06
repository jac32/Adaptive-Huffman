#ifndef HUFFMAN_BITITERATOR_H_
#define HUFFMAN_BITITERATOR_H_

class BitIterator {
  unsigned char byte;
  unsigned char mask;
public: 
  BitIterator(char byte) {
	this->byte = byte;
	this->mask = 0x80;
  }

  bool at_start() { return mask == 0x80; }
  bool at_end() { return mask == 0x1; }
  
  bool next() {
	bool next_bit = byte && mask;
	if (mask > 0x1) mask >>= 1;
	return next_bit;
  }

  bool prev() {
	bool prev_bit = byte && mask;
	if (mask < 0x80) mask <<= 1; 
	return prev_bit;
  }
};

#endif // HUFFMAN_BITITERATOR_H_
