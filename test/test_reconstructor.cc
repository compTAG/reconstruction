#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/reconstructor.h"

class ReconstructorTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::SimplicialComplex SimplicialComplex;

    typedef ctag::Reconstructor<Oracle> Reconstructor;
};


TEST_F(ReconstructorTest, reconstruct_basic_example) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});

    Simplex t_e1({p1, p2});
    Simplex t_e2({p2, p3});
    Simplex t_e3({p3, p1});
    Simplex e1({p2, p4});

    Oracle oracle({ t_e1, t_e2, t_e3, e1 });

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
    EXPECT_EQ(0,0);
};

TEST_F(ReconstructorTest, reconstruct_simple_numerical_error) {
    Point p0({1,4});
    Point p1({12,45});
    Point p2({23,13});

    Simplex e1({p0, p2});
    Simplex e2({p1, p2});

    Oracle oracle({ e1, e2 });

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};

TEST_F(ReconstructorTest, reconstruct_verts_without_edges) {
    Point p0({1,4});
    Point p1({12,45});
    Point p2({23,13});

    Simplex s0({p0, p1});
    Simplex s1({p2});

    Oracle oracle({1, 4, 12, 45, 23, 13}, {0, 1});

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));

    Oracle oracle2({s0, s1});
    EXPECT_TRUE(oracle2.verify(result));
};

TEST_F(ReconstructorTest, reconstruct_failed01) {
    Oracle oracle(
            {54.96624778787091, 52.91420942770391, 43.53223926182769, 13.457994534493356,
            42.0367802087489, 51.35781212657464, 33.03348210038741, 18.443986564691528,
            20.46486340378425, 78.53351478166735, 61.92709663506637, 85.39752926394888,
            29.965467367452312, 49.42368373819278, 26.682727510286664, 84.6561485357468,
            62.11338327692949, 7.964547700906099}, {2, 7, 4, 2, 2, 5, 5, 7, 5, 0, 0, 8, 8,
            5, 2, 0, 6, 2, 4, 6, 3, 6, 3, 2, 1, 2, 1, 0, 1, 8}
    );

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};


TEST_F(ReconstructorTest, reconstruct_failed02) {
    Oracle oracle(
            {22.10453632616526, 6.5075439057193485, 68.62220852374669,
            29.47444647173656, 16.713920310005626, 28.79344409672464,
            39.244246646503065, 82.2466339103433, 61.805234725280926,
            62.61830379602461, 41.1930094858746, 11.047771391367379,
            0.2464881200886171, 0.052881116927605554, 88.40321823721048,
            94.21662328554996, 88.49475383764735, 14.150075772518978,
            30.040968936648092, 42.15965261661597, 58.958186521471454,
            34.64894401485442, 97.8426916014831, 86.97850843971815,
            84.50938221263111, 42.86018123522864}, {7, 4, 4, 11, 11, 7, 3, 4, 7,
            3, 8, 0, 6, 8, 4, 9, 9, 10, 3, 9, 0, 2, 2, 6, 2, 3, 3, 6, 2, 9, 10,
            12, 1, 12, 10, 1, 12, 11, 1, 8, 5, 0, 1, 5, 10, 5, 9, 5, 5, 2}
    );

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};


TEST_F(ReconstructorTest, reconstruct_failed03) {
    Oracle oracle(
            {15.601864044243651, 30.42422429595377, 15.599452033620265,
            52.475643163223786, 5.8083612168199465, 43.194501864211574,
            86.61761457749351, 29.122914019804192, 60.11150117432088,
            61.18528947223795, 70.80725777960456, 13.949386065204184,
            2.0584494295802447, 29.214464853521815, 96.99098521619943,
            36.63618432936917, 83.24426408004217, 45.606998421703594,
            21.233911067827616, 78.51759613930136, 18.182496720710063,
            19.967378215835975, 18.34045098534338, 51.42344384136116}, {11, 4,
            4, 9, 9, 11, 4, 8, 4, 5, 0, 5, 4, 0, 0, 2, 2, 6, 6, 0, 5, 7, 7, 3,
            8, 3, 1, 11, 9, 1, 9, 2, 10, 0, 6, 10, 10, 5}
    );

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};


TEST_F(ReconstructorTest, reconstruct_failed04) {
    Oracle oracle(
            {92.63351350591756, 72.16504565659716, 89.1603438277764,
            49.87803499082658, 68.32767599749869, 44.221278289419416,
            56.688465949967224, 80.24305278044254, 54.696588024303175,
            84.48313057399196, 21.042383598676583, 22.91382044127279,
            76.97544681854357, 96.21675414042492, 89.62301009569732,
            5.891833554567361}, {7, 2, 2, 5, 5, 7, 1, 7, 7, 0, 0, 1, 2, 1, 0, 2,
            3, 2, 0, 3, 6, 3, 0, 6, 6, 4, 4, 3, 4, 5, 5, 3}
    );

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};

TEST_F(ReconstructorTest, reconstruct_failed05) {
    Oracle oracle(
            {21.077063993129396, 42.320175041203164, 61.842176934961024,
            92.61035715268315, 9.828446533689917, 68.19264848723984,
            62.013130987685884, 36.84555913246884, 5.389021959844376,
            85.890985535282, 96.06540578042384, 38.049567998338986,
            98.04293742150735, 9.495426388360773, 52.112765027122386,
            32.48907136368232, 63.65533448355478, 41.511218614249124,
            76.475694826925, 74.22739488503802, 76.49552946168193,
            65.79088675866257, 41.76855795597228, 20.131683134279676,
            76.88053063237426, 80.8487913243346}, {7, 11, 6, 7, 3, 7, 8, 10, 1,
            8, 3, 8, 8, 7, 0, 11, 7, 0, 8, 0, 1, 0, 8, 5, 5, 10, 5, 3, 6, 5, 10,
            9, 9, 1, 9, 12, 5, 9, 5, 12, 2, 1, 1, 4, 4, 2, 2, 0}
    );

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};

TEST_F(ReconstructorTest, reconstruct_failed06) {
    Oracle oracle(
            {50.078252564223234, 79.33254756412906, 14.917816545210815,
            49.521598559800694, 82.0277935819415, 56.057469543671026,
            32.13640316096379, 51.49307699804954, 77.91739971074134,
            28.70133287338482, 81.50803078792227, 18.808979730528876,
            1.4802277281374066, 34.10056357391451, 22.757972836596295,
            26.630933457911144, 71.1731575416301, 20.280881938498652,
            82.11128954998071, 40.766757405984464}, {2, 3, 3, 9, 9, 2, 0, 3, 1,
            3, 0, 1, 7, 1, 6, 7, 7, 3, 8, 7, 7, 5, 5, 8, 8, 3, 3, 4, 4, 9, 4, 5,
            5, 9}
    );

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};

TEST_F(ReconstructorTest, reconstruct_failed07) {
    Oracle oracle(
            {9.240081507565423, 74.68420326825728, 56.197399831267944,
            85.49677477614205, 57.14119651861759, 65.46804603259065,
            3.8956964574643815, 96.62900439556562, 32.654746569377544,
            64.36553274198423, 29.081818399911285, 74.42671715418359,
            51.05631773544871, 83.20025806004527, 30.384681613764787,
            0.5958057194502042, 30.37439848381618, 53.33576729256835,
            14.317216178281733, 92.08275727387559, 3.6330028519636404,
            18.32838663977726, 39.92353379934255, 98.69481821956921},
            {0, 3, 3, 10, 10, 0, 6, 1, 1, 11, 11, 5, 6, 2, 9, 3, 0, 9, 5, 9, 0,
            5, 9, 11, 8, 10, 10, 7, 7, 2, 2, 8, 8, 0, 4, 8, 2, 4, 6, 4, 0, 4}
    );

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};
