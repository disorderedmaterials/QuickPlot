// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "triangle.h"
#include <gtest/gtest.h>
#include <numeric>

namespace UnitTest
{

TEST(TriangleTest, Combine)
{
    std::vector<Triangle> ts = {{{-1, 5, 9}, {4, 8, 3}, {-7, 2, 6}}, {{1, -2, -3}, {-4, -8, -6}, {7, -5, -9}}};

    std::vector<Edge> boxes(ts.size());
    std::transform(ts.begin(), ts.end(), boxes.begin(), [](const auto x) { return x.bounds(); });
    EXPECT_EQ(boxes[1].start.x, -4);
    EXPECT_EQ(boxes[1].start.y, -8);
    EXPECT_EQ(boxes[1].start.z, -9);
    EXPECT_EQ(boxes[1].end.x, 7);
    EXPECT_EQ(boxes[1].end.y, -2);
    EXPECT_EQ(boxes[1].end.z, -3);

    EXPECT_EQ(boxes[0].start.x, -7);
    EXPECT_EQ(boxes[0].start.y, 2);
    EXPECT_EQ(boxes[0].start.z, 3);
    EXPECT_EQ(boxes[0].end.x, 4);
    EXPECT_EQ(boxes[0].end.y, 8);
    EXPECT_EQ(boxes[0].end.z, 9);

    auto bounds = std::reduce(boxes.begin(), boxes.end(), boxes[0], [](const auto a, const auto b) { return a.combine(b); });

    EXPECT_EQ(bounds.start.x, -7);
    EXPECT_EQ(bounds.start.y, -8);
    EXPECT_EQ(bounds.start.z, -9);
    EXPECT_EQ(bounds.end.x, 7);
    EXPECT_EQ(bounds.end.y, 8);
    EXPECT_EQ(bounds.end.z, 9);
}
} // namespace UnitTest
