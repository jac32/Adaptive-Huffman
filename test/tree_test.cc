#include "gtest/gtest.h"

#include "tree.h"

// The fixture for testing class Tree.
class TreeTest : public testing::Test {
protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  TreeTest() {
    // You can do set-up work for each test here.
  }

  virtual ~TreeTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Tree.
};

TEST_F(TreeTest, testContainsMethod) {
  Tree t;

  ASSERT_TRUE(true);
  // Default behaviour should be to return false.
  ASSERT_FALSE(t.contains('a'));
  ASSERT_FALSE(t.contains('b'));
  
  // The first occurence should switch the contains result.
  t.update('a'); 
  ASSERT_TRUE(t.contains('a'));
  ASSERT_FALSE(t.contains('b'));

  // Additional occurences shouldn't affect the result.
  // But new characters should still change the result.
  t.update('b');
  ASSERT_TRUE(t.contains('a'));
  ASSERT_TRUE(t.contains('b'));

  // Repeated occurrences should not affect results.
  t.update('a');
  t.update('a');
  ASSERT_TRUE(t.contains('a'));
  ASSERT_TRUE(t.contains('b'));
}



