#include "bitdump.h"

#define BYTE_LENGTH (8)

BitDump::BitDump(std::ostream& output, size_t capacity) : output(output) {
  this->capacity = capacity;
  buffer = std::deque<bool>();
}

// TODO: properly handle EOS
BitDump::~BitDump() {
  flush();
  
  std::cout << "Remaining: " << buffer.size() << std::endl;
}

void BitDump::flush() {
  unsigned char bit, byte = 0;

  while (buffer.size() >= BYTE_LENGTH) {
	for (int i = 1; i <= BYTE_LENGTH; ++i) {
	  bit = buffer.back();
	  bit <<= BYTE_LENGTH - i;
	  byte |= bit;
	  buffer.pop_back();
	}
	std::cout << "Writing " << std::bitset<8>(byte) << std::endl;
	output << byte;
  }
}

void BitDump::push(bool input) {
  if (buffer.size() >= capacity) flush();
  buffer.push_front(input);
}

void BitDump::push_byte(char input) {
   unsigned char mask = 0x80;
   while (mask > 0) {
	 push(mask & input);
	 mask >>= 1;
   }
}

// BitDump& BitDump::operator<<(bool input) {
//   this->push(input);
//   return (*this)&;
// }
