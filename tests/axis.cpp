#include "axis.h"
#include "logAxis.h"
#include <algorithm>
#include <gtest/gtest.h>

namespace UnitTest
{

void matchAxes(Axis &axis, std::vector<double> &points, std::vector<double> &coords)
{
    axis.dataChanged();
    ASSERT_EQ(axis.tickCount(), points.size());
    ASSERT_EQ(axis.tickCount(), coords.size());

    for (int i = 0; i < axis.tickCount(); i++)
    {
        EXPECT_DOUBLE_EQ(points[i], axis.tick(i));
        EXPECT_DOUBLE_EQ(coords[i], axis.tickCoord(i));
    }
}

TEST(AxisTest, LinearMarks)
{
    Axis axis;
    axis.setMinimum(-11.0);
    axis.setMaximum(11.0);

    std::vector<double> points = {-10, -5, 0, 5, 10};
    std::vector<double> coords = {2.0 / 11.0, 6.0 / 11.0, 1.0, 16.0 / 11.0, 21.0 / 11.0};

    matchAxes(axis, points, coords);
}

TEST(AxisTest, LogMarks)
{
    LogAxis axis;
    axis.setMinimum(0.1);
    axis.setMaximum(10.0);

    std::vector<double> points = {0.1, 0.2, 0.3, 0.5, 0.8, 1.0, 2.0, 3.0, 5.0, 8.0, 10.0};
    std::vector<double> coords(points.size());
    std::transform(points.begin(), points.end(), coords.begin(), [](const auto x) { return log10(x) + 1.0; });

    matchAxes(axis, points, coords);
}

} // namespace UnitTest
