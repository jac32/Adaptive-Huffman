/// @file buffer.h
/// @author 140013444 
/// @date 7 Oct 2016
/// @brief Buffer structures for converting between bit/byte streams.
///
/// Three classes are provided.
/// - A Buffer base class, providing the common functionality of a simple bit/byte queue
/// - A specialized InputBuffer which wraps an istream of bytes and ptrovides a queue of bits/bytes.
/// - A specialized OutputBuffer which wraps an ostream of bytes and ptrovides a queue of bits/bytes.
///
/// There's plenty of room for optimization and improvement here but, as the focus of the pratical
/// should be on the  compression algorithm, the implementation is pretty barebones.
#ifndef HUFFMAN_BUFFER_H_
#define HUFFMAN_BUFFER_H_

#include <iostream>
#include <queue>

typedef unsigned char byte;
typedef bool bit;


/// @brief Base class for bit/byte stream conversion via buffer.
///
/// Encapsulating the common behavior of the InputBuffer and OutputBuffer.
class Buffer : public std::queue<bit> {
  size_t capacity;
 public:
  Buffer(size_t capacity = 8);
  size_t get_capacity();
  byte pop_byte(); 
  void push_byte(byte input);
};


class InputBuffer : public Buffer {
  std::istream& stream;

public: 
  InputBuffer(std::istream& stream, size_t = 8); 

  byte receive_byte();
  bit receive_bit();

  bool eof();
};


class OutputBuffer : public Buffer {
  std::ostream& stream;

public:
  OutputBuffer(std::ostream& stream, size_t = 8);
  ~OutputBuffer();

  void flush(bool = false);

  void send_byte(byte out_byte);
  void send_bit(bit bit);
};

#endif // HUFFMAN_INPUTBUFFER_H_
