#include "gtest/gtest.h"

#include <sstream>

#include "tree.h"


class EndToEndTest : public ::testing::Test {
protected:
  Tree *encoder;
  Tree *decoder;
  std::stringstream input;
  std::stringstream middle;
  std::stringstream output;

  virtual void SetUp() {
	encoder = new Tree(input, middle);
	decoder = new Tree(middle, output);
  } 

  virtual void TearDown() {
	delete encoder;
	delete decoder;
  }
};

TEST_F(EndToEndTest, HandlesEmptyString) {
  input << "";
  encoder->encode();
  decoder->decode();
  ASSERT_EQ(output.get(), -1);
}

TEST_F(EndToEndTest, HandlesSingleChar) {
  input << "a";
  encoder->encode();
  decoder->decode();
  ASSERT_EQ(output.get(), 'a');
}

TEST_F(EndToEndTest, HandlesDoubleChar) {
  input << "bb";
  encoder->encode();
  decoder->decode();
  ASSERT_EQ(std::string("bb"), output.str());
}

TEST_F(EndToEndTest, HandlesHelloWorld) {
  input << "Hello, World!";
  encoder->encode();
  decoder->decode();
  ASSERT_EQ(std::string("Hello, World!"), output.str());
}

TEST_F(EndToEndTest, HandlesMultiLines) {
  std::stringstream expected;
  input << "multi" << std::endl << "line" << std::endl << "message";
  expected << "multi" << std::endl << "line" << std::endl << "message";
  encoder->encode();
  decoder->decode();
  ASSERT_EQ(expected.str(), output.str());
}
