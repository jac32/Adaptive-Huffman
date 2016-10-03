#ifndef HUFFMAN_BITDUMP_H_
#define HUFFMAN_BITDUMP_H_

#include <iostream>
#include <deque>

class BitDump {
  size_t capacity;
  std::deque<bool> buffer;
  std::ostream& output;

public:
  BitDump(std::ostream&, size_t = 8);
  ~BitDump();
  void flush();
  void push(bool input);
  void push_byte(char input);
  //  BitDump& operator<<(bool input);
};

#endif // HUFFMAN_BITDUMP_H_
