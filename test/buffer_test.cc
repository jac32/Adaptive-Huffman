#include "gtest/gtest.h"

#include "buffer.h"

TEST(BaseBufferTest, HandlesSimplePushPop) {
  Buffer b;

  b.push_byte('a');
  b.push_byte('b');
  b.push_byte('c');
  b.push_byte('d');

  EXPECT_EQ(b.pop_byte(), 'a');
  EXPECT_EQ(b.pop_byte(), 'b');
  EXPECT_EQ(b.pop_byte(), 'c');
  EXPECT_EQ(b.pop_byte(), 'd');
}

TEST(BaseBufferTest, HandlesSizeAndCapacity) {
  Buffer standard;
  Buffer non_standard(16);

  EXPECT_EQ(standard.get_capacity(), 8);
  EXPECT_EQ(non_standard.get_capacity(), 16);

  EXPECT_EQ(standard.size(), 0);
  EXPECT_EQ(non_standard.size(), 0);

  standard.push_byte('a');
  non_standard.push_byte('a');

  EXPECT_EQ(standard.size(), 8);
  EXPECT_EQ(non_standard.size(), 8);

  standard.push_byte('b');
  non_standard.push_byte('b');

  EXPECT_EQ(standard.size(), 16);
  EXPECT_EQ(non_standard.size(), 16);

  EXPECT_NE(standard.pop_byte(), -1);
  EXPECT_NE(non_standard.pop_byte(), -1);

  EXPECT_EQ(standard.size(), 8);
  EXPECT_EQ(non_standard.size(), 8);

  EXPECT_NE(standard.pop_byte(), -1);
  EXPECT_NE(non_standard.pop_byte(), -1);

  EXPECT_EQ(standard.size(), 0);
  EXPECT_EQ(non_standard.size(), 0);

  EXPECT_EQ(standard.pop_byte(), -1);
  EXPECT_EQ(non_standard.pop_byte(), -1);
}

// TODO: Find the reason this isn't as expected
TEST(InputBufferTest, HandlesCapacity) {
  std::stringstream s("Hello, World!");
  InputBuffer ib(s);
  InputBuffer bigger_ib(s, 10);
  InputBuffer biggest_ib(s, 16);

  EXPECT_EQ(ib.size(), 8);
  EXPECT_EQ(bigger_ib.size(), 8);
  EXPECT_EQ(biggest_ib.size(), 16);

  for (int i = 0; i < 6; ++i) {
	ib.receive_bit();
	bigger_ib.receive_bit();
	biggest_ib.receive_bit();
  }

  EXPECT_EQ(ib.size(), 2);
  EXPECT_EQ(bigger_ib.size(), 2);
  EXPECT_EQ(biggest_ib.size(), 10);

  ib.receive_byte();
  bigger_ib.receive_byte();
  biggest_ib.receive_byte();
  
  EXPECT_EQ(ib.size(), 2);
  EXPECT_EQ(bigger_ib.size(), 2);
  EXPECT_EQ(biggest_ib.size(), 14);
   
}

TEST(InputBufferTest, HandlesEmptyStream) {
  std::stringstream s;
  InputBuffer ib(s);

  EXPECT_EQ(ib.size(), 0);
  EXPECT_EQ(ib.receive_byte(), -1);
  EXPECT_EQ(ib.receive_bit(), -1);
}


TEST(OutputBufferTest, HandlesPadding) {
  
}

TEST(OutputBufferTest, HandlesFlushing) {
}

