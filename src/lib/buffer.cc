#include <assert.h>

#include "buffer.h"

//================================================================================ 
// Base Class
//================================================================================ 

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


//================================================================================ 
// Input Buffer
//================================================================================ 

InputBuffer::InputBuffer(std::istream& stream) : stream(stream) {
  int next;
  if ((next = stream.get()) != -1) {
	push_byte(next);
  }
}

int InputBuffer::receive_byte() {
  int next;
  if (size() >= 8) {
	return pop_byte();
  }
  else if ((next = stream.get()) != -1) {
	return push_byte(next), pop_byte();
  }
  else {
	return -1;
  }
}

int InputBuffer::receive_bit() {
  int next;
  if (empty()) {
	if ((next = stream.get()) != -1) {
	  push_byte(next);
	}
	else {
	  return -1;
	}
  }
  next = front();
  return pop(), next;
}


//================================================================================ 
// Output Buffer
//================================================================================ 
OutputBuffer::OutputBuffer(std::ostream& stream) : stream(stream) {}

OutputBuffer::~OutputBuffer() {
  while (size() > 0) {
	send_bit(0); 
  }
}

void OutputBuffer::flush(bool force) {
  while (size() >= 8) {
	stream << (char) pop_byte();
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
