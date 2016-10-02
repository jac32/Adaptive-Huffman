#include "bitdump.h"

#define BYTE_LENGTH (8)

BitDump::BitDump(std::ostream& output, size_t capacity) : output(output) {
  this->capacity = capacity;
  buffer = std::deque<bool>();
}

BitDump::~BitDump() {
  std::cout << "Clearing out buffer..." << std::endl;
}

void BitDump::flush() {
  std::cout << "Flushing buffer (BA)..." << std::endl;

  unsigned char bit, byte = 0;

  while (buffer.size() > BYTE_LENGTH) {
	for (int i = 1; i <= BYTE_LENGTH; ++i) {
	  bit = buffer.back();
	  bit <<= BYTE_LENGTH - i;
	  byte |= bit;
	  buffer.pop_back();
	}
  }
}

void BitDump::push(bool input) {
  std::cout << "buffer size: " << buffer.size() << " ";
  std::cout << "Pushing bit: " << (int) input;
  std::cout << "..." << std::endl;
  if (buffer.size() >= capacity) flush();
  buffer.push_front(input);
}

// BitDump& BitDump::operator<<(bool input) {
//   this->push(input);
//   return (*this)&;
// }
