
#include <gtest/gtest.h>

#include "ctag/types.h"
#include "ctag/filtration_line.h"
#include "ctag/diagram.h"

#include "ctag/filtration_line_factory.h"

class FiltrationLineFactoryTest : public ::testing::Test {
public:
    typedef ctag::Types::Direction Direction;
    typedef ctag::FiltrationLine<Direction> FiltrationLine;
    typedef ctag::Diagram Diagram;

    typedef ctag::FiltrationLineFactory<FiltrationLine, Diagram> FiltrationLineFactory;
    typedef std::vector<FiltrationLine> Lines;
};

TEST_F(FiltrationLineFactoryTest, make_filtration_lines) {
    Direction direction({0, 1});
    Diagram diagram(direction);
    diagram.push_back(4, 0, 0);
    diagram.push_back(6, 10, 0);
    diagram.push_back(2, 20, 0);
    diagram.push_back(0, 30, 0);
    diagram.push_back(1, 40, 0);
    diagram.push_back(5, 50, 0);

    FiltrationLineFactory factory;

    Lines lines;
    factory.make_filtration_lines(std::back_inserter(lines), diagram);

    Lines::const_iterator line = lines.begin();
    EXPECT_EQ(0, line->a());
    EXPECT_EQ(1, line->b());
    EXPECT_EQ(0, line->c());

    line++;
    EXPECT_EQ(0, line->a());
    EXPECT_EQ(1, line->b());
    EXPECT_EQ(-1, line->c());

    line++;
    EXPECT_EQ(0, line->a());
    EXPECT_EQ(1, line->b());
    EXPECT_EQ(-2, line->c());

    line++;
    EXPECT_EQ(0, line->a());
    EXPECT_EQ(1, line->b());
    EXPECT_EQ(-4, line->c());

    line++;
    EXPECT_EQ(0, line->a());
    EXPECT_EQ(1, line->b());
    EXPECT_EQ(-5, line->c());

    line++;
    EXPECT_EQ(0, line->a());
    EXPECT_EQ(1, line->b());
    EXPECT_EQ(-6, line->c());
};
