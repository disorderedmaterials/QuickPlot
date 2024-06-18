// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "scatterGeometry.h"
#include "triangle.h"
#include <algorithm>

ScatterGeometry::ScatterGeometry() : PlotGeometry() {}

std::vector<Triangle> ScatterGeometry::faces_(std::vector<Point> ps) const
{
    const int N = ps.size();

    std::vector<Triangle> ts(2 * N);
    for (int i = 0; i < N; i++)
    {
        Triangle t(ps[i], ps[i], ps[i]);
        t.a.x -= thickness_;
        t.a.y -= thickness_;
        t.b.x += thickness_;
        t.b.y -= thickness_;
        t.c.x += thickness_;
        t.c.y += thickness_;
        ts[2 * i] = t;

        t = Triangle(ps[i], ps[i], ps[i]);
        t.a.x -= thickness_;
        t.a.y -= thickness_;
        t.b.x += thickness_;
        t.b.y += thickness_;
        t.c.x -= thickness_;
        t.c.y += thickness_;
        ts[2 * i + 1] = t;
    }

    return ts;
}
