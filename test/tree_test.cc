#include "gtest/gtest.h"

#include "tree.h"

TEST(TreeTest, testContainsMethod) {
  Tree t;

  EXPECT_TRUE(true);
  // Default behaviour should be to return false.
  EXPECT_FALSE(t.contains('a'));
  EXPECT_FALSE(t.contains('b'));
  
  // The first occurence should switch the contains result
  t.process_symbol('a'); 
  EXPECT_TRUE(t.contains('a'));
  EXPECT_FALSE(t.contains('b'));

  // Additional occurences shouldn't affect the result
  // But new characters should still change the result
  t.process_symbol('b');
  EXPECT_TRUE(t.contains('a'));
  EXPECT_TRUE(t.contains('b'));

  // Repeated occurrences should not affect results.
  t.process_symbol('a');
  t.process_symbol('a');
  EXPECT_TRUE(t.contains('a'));
  EXPECT_TRUE(t.contains('b'));
}

TEST(TreeTest, testWeightAfterAddition) {
  Tree t;
  EXPECT_EQ(t.total_weight(), 0);
  // First occurence of any symbol should increment once 
  t.process_symbol('a');
  EXPECT_EQ(t.total_weight(), 1);

  // New symbols should also increment the weight
  t.process_symbol('b');
  EXPECT_EQ(t.total_weight(), 2);

  // Further reptition should be counted
  t.process_symbol('a');
  EXPECT_EQ(t.total_weight(), 3);
}


TEST(TreeTest, testWeightGroups) {
  Tree t;
  for (char c: "abccdd") t.process_symbol(c);
  EXPECT_EQ(t.get_weight_group(1)->get_symbol(), 'a');
  EXPECT_EQ(t.get_weight_group(1)->group_next()->get_symbol(), 'b');
  EXPECT_EQ(t.get_weight_group(2)->get_symbol(), 'c');
  EXPECT_EQ(t.get_weight_group(2)->group_next()->get_symbol(), 'd');

}
