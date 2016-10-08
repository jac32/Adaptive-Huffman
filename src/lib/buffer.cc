#include "buffer.h"

//================================================================================ 
// Base Class
//================================================================================ 

Buffer::Buffer(size_t capacity) {
  this->capacity = capacity;
}

int Buffer::pop_byte() {
  if (empty()) return -1;

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
  int next_val;
  while ((next_val = stream.get()) != -1 && size() <= get_capacity() - 8) {
	  push_byte(next_val);
  }
}

int InputBuffer::receive_byte() {
  int next = stream.get();
  if (next == -1)
	return next;

  if (next != -1) {
	push_byte(next);
	return pop_byte();
  }
  else if (size() > 0) {
	while (size() < 8) {
	  push(0);
	}
	return pop_byte();
  }

  return -1;
}

int InputBuffer::receive_bit() {
  int next_val = stream.get(); 
  if (next_val == -1) {
	return -1;
  }
  else if (empty() && next_val != -1) {
	push_byte(next_val);
  }
  next_val = front(); pop();
  return next_val;
}


//================================================================================ 
// Output Buffer
//================================================================================ 
OutputBuffer::OutputBuffer(std::ostream& stream, size_t capacity) : Buffer(capacity), stream(stream) {}

OutputBuffer::~OutputBuffer() {
  while (size() > 0) {
	send_bit(0); 
  }
}

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
