// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "triangle.h"
#include <gtest/gtest.h>
#include <numeric>

namespace UnitTest
{

TEST(QuadTest, Combine)
{
    std::vector<Quad> ts = {{{-1, 5, 9}, {4, 8, 3}, {-7, 2, 6}, {6, 4, -3}},
                            {{1, -2, -3}, {-4, -8, -6}, {7, -5, -9}, {3, -4, 6}}};

    std::vector<Edge> boxes(ts.size());
    std::transform(ts.begin(), ts.end(), boxes.begin(), [](const auto x) { return x.bounds(); });
    EXPECT_EQ(boxes[1].start.x, -4);
    EXPECT_EQ(boxes[1].start.y, -8);
    EXPECT_EQ(boxes[1].start.z, -9);
    EXPECT_EQ(boxes[1].end.x, 7);
    EXPECT_EQ(boxes[1].end.y, -2);
    EXPECT_EQ(boxes[1].end.z, 6);

    EXPECT_EQ(boxes[0].start.x, -7);
    EXPECT_EQ(boxes[0].start.y, 2);
    EXPECT_EQ(boxes[0].start.z, -3);
    EXPECT_EQ(boxes[0].end.x, 6);
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

TEST(QuadTest, Cut)
{
    Vec3<float> i{1, 2, 3}, j{4, 5, 6}, k{7, 8, 9}, l{10, 11, 12};
    Quad q{i, j, k, l};
    auto [first, second] = q.asTriangles();

    EXPECT_EQ(first.a, i);
    EXPECT_EQ(first.b, j);
    EXPECT_EQ(first.c, k);

    EXPECT_EQ(second.a, k);
    EXPECT_EQ(second.b, l);
    EXPECT_EQ(second.c, i);
}
} // namespace UnitTest
