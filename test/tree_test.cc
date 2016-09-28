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

    // simple_tree.count_symbol('a');
    // simple_tree.count_symbol('b');
    // simple_tree.count_symbol('c');
  }
};


TEST_F(TreeTest, testContainsMethod) {
  Tree *t = new Tree();//empty_tree;

  EXPECT_TRUE(true);
  // Default behaviour should be to return false.
  EXPECT_FALSE(t->contains('a'));
  EXPECT_FALSE(t->contains('b'));
  
  // The first occurence should switch the contains result
  t->count_symbol('a'); 
  EXPECT_TRUE(t->contains('a'));
  EXPECT_FALSE(t->contains('b'));

  // Additional occurences shouldn't affect the result
  // But new characters should still change the result
  t->count_symbol('b');
  EXPECT_TRUE(t->contains('a'));
  EXPECT_TRUE(t->contains('b'));

  // Repeated occurrences should not affect results.
  t->count_symbol('a');
  t->count_symbol('a');
  EXPECT_TRUE(t->contains('a'));
  EXPECT_TRUE(t->contains('b'));

  delete t;
}


