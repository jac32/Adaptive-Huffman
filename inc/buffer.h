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
/// Encapsulates the common behavior of the InputBuffer and OutputBuffer.
class Buffer : public std::queue<bit> {

  size_t capacity;  ///< The maximum number of bits desired to be buffered at any given time

public:
  Buffer(size_t capacity = 8);  ///< Standard constructor

  int pop_byte();             ///< Pops and returns a full byte from the buffer
  void push_byte(byte input);  ///< Pushes a full byte to the buffer

  size_t get_capacity();  ///< Gets the maximum buffer size (in bits)
};

/// @brief Buffers input bytestream and provides bitwise operations 
///
/// Data streams are typically bytestreams, but the compression algorithms require bitstreams.
/// This class buffers up bytes from the stream and provides convenient bitwise accessors
class InputBuffer : private Buffer {

  std::istream& stream; ///< The input bytestream

public: 
  InputBuffer(std::istream& stream, size_t = 8);  ///< Standard constructor

  int receive_byte();  ///< Obtain the next full byte from the buffer
  int receive_bit();    ///< Obtain the next bit from the buffer

  using Buffer::empty;
  using Buffer::size;
};

/// @brief Buffers output bytestream and provides bitwise operations 
///
/// Data streams are typically bytestreams, but the compression algorithms require bitstreams.
/// This class buffers up bits and provides convenient bitwise push functions
class OutputBuffer : private Buffer {

  std::ostream& stream;  ///< The output bytestream

public:
  OutputBuffer(std::ostream& stream, size_t = 8);  ///< Standard constructor
  ~OutputBuffer();                                 ///< Pads to a full byte with 0 bits

  void flush(bool = false);  ///< flush all full bytes from the buffer

  void send_byte(byte out_byte);  ///< Push a full byte into the buffer (may flush)
  void send_bit(bit bit);         ///< Push a single bit into the buffer (may flush)

  using Buffer::empty;
  using Buffer::size;
};

#endif // HUFFMAN_INPUTBUFFER_H_
