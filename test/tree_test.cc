#include "gtest/gtest.h"

#include "tree.h"

// The fixture for testing class Tree.
class TreeTest : public testing::Test {
protected:
  Tree empty_tree;
  Tree simple_tree;

  TreeTest() {
    // empty_tree = Tree();
    // simple_tree = Tree();

    // simple_tree.update_symbol('a');
    // simple_tree.update_symbol('b');
    // simple_tree.update_symbol('c');
  }
};


TEST_F(TreeTest, testContainsMethod) {
  Tree t;

  EXPECT_TRUE(true);
  // Default behaviour should be to return false.
  EXPECT_FALSE(t.contains('a'));
  EXPECT_FALSE(t.contains('b'));
  
  // The first occurence should switch the contains result
  t.update_symbol('a'); 
  EXPECT_TRUE(t.contains('a'));
  EXPECT_FALSE(t.contains('b'));

  // Additional occurences shouldn't affect the result
  // But new characters should still change the result
  t.update_symbol('b');
  EXPECT_TRUE(t.contains('a'));
  EXPECT_TRUE(t.contains('b'));

  // Repeated occurrences should not affect results.
  t.update_symbol('a');
  t.update_symbol('a');
  EXPECT_TRUE(t.contains('a'));
  EXPECT_TRUE(t.contains('b'));
}


