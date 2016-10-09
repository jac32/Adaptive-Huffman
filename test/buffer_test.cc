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

TEST(BaseBufferTest, HandlesSize) {
  Buffer standard;
  EXPECT_EQ(standard.size(), 0);

  standard.push_byte('a');
  EXPECT_EQ(standard.size(), 8);

  standard.push_byte('b');
  EXPECT_EQ(standard.size(), 16);

  EXPECT_NE(standard.pop_byte(), -1);
  EXPECT_EQ(standard.size(), 8);

  EXPECT_NE(standard.pop_byte(), -1);
  EXPECT_EQ(standard.size(), 0);

  EXPECT_EQ(standard.pop_byte(), -1);
}

TEST(InputBufferTest, HandlesEmptyStream) {
  std::stringstream s;
  InputBuffer ib(s);

  std::cerr << "Here it is: " << ib.size() << std::endl;
  
  ASSERT_TRUE(ib.empty());
  EXPECT_EQ(ib.receive_byte(), -1);
  EXPECT_EQ(ib.receive_bit(), -1);
}


TEST(OutputBufferTest, HandlesPadding) {
  
}

TEST(OutputBufferTest, HandlesFlushing) {
}

