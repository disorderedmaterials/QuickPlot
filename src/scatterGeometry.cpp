// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "scatterGeometry.h"
#include "triangle.h"
#include <algorithm>

ScatterGeometry::ScatterGeometry() : PlotGeometry() {}

std::vector<Triangle> ScatterGeometry::faces_(std::vector<Vec3<float>> ps) const
{
    const int N = ps.size();

    const int SIDES = 6;

    std::vector<Triangle> ts(SIDES * 2 * N);
    for (int i = 0; i < N; i++)
    {
        Quad t;
        t = Quad(ps[i], ps[i], ps[i], ps[i]);
        t = t - zhat * thickness_;
        t.a -= (xhat + yhat) * thickness_;
        t.b += (xhat - yhat) * thickness_;
        t.c += (xhat + yhat) * thickness_;
        t.d -= (xhat - yhat) * thickness_;
        {
            auto [first, second] = t.asTriangles();
            ts[2 * SIDES * i] = first;
            ts[2 * SIDES * i + 1] = second;
        }

        t = Quad(ps[i], ps[i], ps[i], ps[i]);
        t = t + zhat * thickness_;
        t.a -= (xhat + yhat) * thickness_;
        t.b += (xhat - yhat) * thickness_;
        t.c += (xhat + yhat) * thickness_;
        t.d -= (xhat - yhat) * thickness_;
        {
            auto [first, second] = t.flip().asTriangles();
            ts[2 * SIDES * i + 2] = first;
            ts[2 * SIDES * i + 3] = second;
        }

        t = Quad(ps[i], ps[i], ps[i], ps[i]);
        t = t + xhat * thickness_;
        t.a -= (zhat + yhat) * thickness_;
        t.b += (zhat - yhat) * thickness_;
        t.c += (zhat + yhat) * thickness_;
        t.d -= (zhat - yhat) * thickness_;
        {
            auto [first, second] = t.asTriangles();
            ts[2 * SIDES * i + 4] = first;
            ts[2 * SIDES * i + 5] = second;
        }

        t = Quad(ps[i], ps[i], ps[i], ps[i]);
        t = t - xhat * thickness_;
        t.a -= (zhat + yhat) * thickness_;
        t.b += (zhat - yhat) * thickness_;
        t.c += (zhat + yhat) * thickness_;
        t.d -= (zhat - yhat) * thickness_;
        {
            auto [first, second] = t.flip().asTriangles();
            ts[2 * SIDES * i + 6] = first;
            ts[2 * SIDES * i + 7] = second;
        }

        t = Quad(ps[i], ps[i], ps[i], ps[i]);
        t = t + yhat * thickness_;
        t.a -= (xhat + zhat) * thickness_;
        t.b += (xhat - zhat) * thickness_;
        t.c += (xhat + zhat) * thickness_;
        t.d -= (xhat - zhat) * thickness_;
        {
            auto [first, second] = t.asTriangles();
            ts[2 * SIDES * i + 8] = first;
            ts[2 * SIDES * i + 9] = second;
        }

        t = Quad(ps[i], ps[i], ps[i], ps[i]);
        t = t - yhat * thickness_;
        t.a -= (xhat + zhat) * thickness_;
        t.b += (xhat - zhat) * thickness_;
        t.c += (xhat + zhat) * thickness_;
        t.d -= (xhat - zhat) * thickness_;
        {
            auto [first, second] = t.flip().asTriangles();
            ts[2 * SIDES * i + 10] = first;
            ts[2 * SIDES * i + 11] = second;
        }
    }

    return ts;
}
