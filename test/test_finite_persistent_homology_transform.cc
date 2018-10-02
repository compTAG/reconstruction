#include <gtest/gtest.h>

#include "ctag/finite_persistent_homology_transform.h"

class FinitePersistentHomologyTransformTest : public ::testing::Test {
public:
    typedef ctag::FinitePersistentHomologyTransform FinitePersistentHomologyTransform;
};

TEST_F(FinitePersistentHomologyTransformTest, constructor_default) {
    FinitePersistentHomologyTransform::Pair pair;
    EXPECT_EQ(0, pair.birth);
    EXPECT_EQ(0, pair.death);

}

TEST_F(FinitePersistentHomologyTransformTest, constructor_nondefault) {
    FinitePersistentHomologyTransform::Pair pair;
    pair = FinitePersistentHomologyTransform::Pair(1,2);
    EXPECT_EQ(1, pair.birth);
    EXPECT_EQ(2, pair.death);
}

// TEST_F(FinitePersistentHomologyTransformTest, const_iterator) {
//     FinitePersistentHomologyTransform::const_iterator diag;
//     diag = FinitePersistentHomologyTransform::Pair(1,2);
// 
//     diag.push_back(2,4)
//     diag.push_back(5,7)
//     diag.push_back(8,9)


//    EXPECT_EQ(2, diag.birth);
//    EXPECT_EQ(4, diag.death);

//    diag++
//
//    EXPECT_EQ(5, diag.death);
//    EXPECT_EQ(7, diag.death);
//
//    diag++
//
//    EXPECT_EQ(8, diag.death);
//    EXPECT_EQ(9, diag.death);
// }


