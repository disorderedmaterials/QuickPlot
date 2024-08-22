// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "scatterGeometry.h"
#include "triangle.h"
#include <algorithm>

ScatterGeometry::ScatterGeometry() : PlotGeometry() {}

std::vector<Triangle> ScatterGeometry::faces_(std::vector<Vec3<float>> ps) const
{
    const int N = ps.size();

    std::vector<Triangle> ts(2 * N);
    for (int i = 0; i < N; i++)
    {
        Triangle t(ps[i], ps[i], ps[i]);
        t.a -= (xhat + yhat) * thickness_;
        t.b += (xhat - yhat) * thickness_;
        t.c += (xhat + yhat) * thickness_;
        ts[2 * i] = t + zhat * thickness_;

        t = Triangle(ps[i], ps[i], ps[i]);
        t.a -= (xhat + yhat) * thickness_;
        t.b += (yhat + xhat) * thickness_;
        t.c += (yhat - xhat) * thickness_;
        ts[2 * i + 1] = t + zhat * thickness_;
    }

    return ts;
}
