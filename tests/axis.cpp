#include "axis.h"
#include "logAxis.h"
#include <gtest/gtest.h>

namespace UnitTest
{

void matchAxes(Axis &axis, std::vector<double> &points)
{
    axis.dataChanged();
    ASSERT_EQ(axis.tickCount(), points.size());

    for (int i = 0; i < axis.tickCount(); i++)
    {
        EXPECT_DOUBLE_EQ(points[i], axis.tick(i));
    }
}

TEST(AxisTest, LinearMarks)
{
    Axis axis;
    axis.setMinimum(-11.0);
    axis.setMaximum(11.0);

    std::vector<double> points = {-10, -5, 0, 5, 10};

    matchAxes(axis, points);
}

TEST(AxisTest, LogMarks)
{
    LogAxis axis;
    axis.setMinimum(0.1);
    axis.setMaximum(10.0);

    std::vector<double> points = {0.1, 0.2, 0.3, 0.5, 0.8, 1.0, 2.0, 3.0, 5.0, 8.0, 10.0};

    matchAxes(axis, points);
}

} // namespace UnitTest
