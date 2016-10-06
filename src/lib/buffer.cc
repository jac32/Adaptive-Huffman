#include "buffer.h"

//================================================================================ 
// Base Class
//================================================================================ 

Buffer::Buffer(size_t capacity) {
  this->capacity = capacity;
}

byte Buffer::pop_byte() {
  bool next;
  byte output = 0x0; 
  byte mask = 0x80;

  for (int i = 0; i < 8; ++i) {
	next = front();
	pop();
	if (next) output |= (mask >> i);
  }
  return output;
}

void Buffer::push_byte(byte input) {
  byte mask = 0x80;

  for (int i = 0; i < 8; ++i) {
	push(mask >> i & input);
  }
}

size_t Buffer::get_capacity() { return capacity; }

//================================================================================ 
// Input Buffer
//================================================================================ 

InputBuffer::InputBuffer(std::istream& stream, size_t capacity) : Buffer(capacity), stream(stream) {
  while (size() < get_capacity()) {
	push_byte(stream.get());
  }
}

byte InputBuffer::receive_byte() {
  push_byte(stream.get());
  push_byte(stream.get());
  return pop_byte();
}

bit InputBuffer::receive_bit() {
  if (empty()) {
	push_byte(stream.get());
  }
  bit retval = front();
  pop();
  return retval;
}


//================================================================================ 
// Output Buffer
//================================================================================ 
OutputBuffer::OutputBuffer(std::ostream& stream, size_t capacity) : Buffer(capacity), stream(stream) {}

void OutputBuffer::flush(bool force) {
  if (size() >= get_capacity() || force) {
	while (size() >= 8) {
	  stream << pop_byte();
	}
  }
}

void OutputBuffer::send_byte(byte out_byte) {
  push_byte(out_byte);
  flush();
}

void OutputBuffer::send_bit(bit out_bit) {
  push(out_bit);
  flush();
}
