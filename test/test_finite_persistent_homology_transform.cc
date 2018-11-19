#include <gtest/gtest.h>

#include "ctag/finite_persistent_homology_transform.h"

class FinitePersistentHomologyTransformTest : public ::testing::Test {
public:
  typedef ctag::FinitePersistentHomologyTransform fpht;
};

// Test constructor of pair w/ default
TEST_F(FinitePersistentHomologyTransformTest, pair_constructor_default) {
    fpht::Pair pair;
    EXPECT_EQ(0, pair.birth);
    EXPECT_EQ(0, pair.death);

}

// Test constructor of pair w/ nondefault
TEST_F(FinitePersistentHomologyTransformTest, pair_constructor_nondefault) {
    fpht::Pair pair;
    pair = fpht::Pair(1,2);
    EXPECT_EQ(1, pair.birth);
    EXPECT_EQ(2, pair.death);
}

// Test constructor diagram
TEST_F(FinitePersistentHomologyTransformTest, diagram_constructor) {
  fpht::Pair pair1;
  fpht::Pair pair2;
  pair1 = fpht::Pair(1,2);
  pair2 = fpht::Pair(3,4);
  fpht::Diagram diag1;
  diag1.push_back(pair1);
  diag1.push_back(pair2);
  EXPECT_EQ(1, diag1[0].birth);
  EXPECT_EQ(2, diag1[0].death);
  EXPECT_EQ(3, diag1[1].birth);
  EXPECT_EQ(4, diag1[1].death);
}


// Test construction of a pht
TEST_F(FinitePersistentHomologyTransformTest, pht_constructor) {
  fpht::Pair pair1;
  fpht::Pair pair2;
  pair1 = fpht::Pair(1,2);
  pair2 = fpht::Pair(3,4);
  fpht::Diagram diag1;
  diag1.push_back(pair1);
  diag1.push_back(pair2);
  fpht::Pair pair3;
  fpht::Pair pair4;
  pair3 = fpht::Pair(5,6);
  pair4 = fpht::Pair(7,8);
  fpht::Diagram diag2;
  diag2.push_back(pair3);
  diag2.push_back(pair4);
  fpht::FPHT fpht1;
  fpht1[0] = diag1;
  fpht1[1] = diag2;
  EXPECT_EQ(1, (fpht1[0])[0].birth);
  EXPECT_EQ(2, (fpht1[0])[0].death);
  EXPECT_EQ(3, (fpht1[0])[1].birth);
  EXPECT_EQ(4, (fpht1[0])[1].death);
  EXPECT_EQ(5, (fpht1[1])[0].birth);
  EXPECT_EQ(6, (fpht1[1])[0].death);
  EXPECT_EQ(7, (fpht1[1])[1].birth);
  EXPECT_EQ(8, (fpht1[1])[1].death);
}


