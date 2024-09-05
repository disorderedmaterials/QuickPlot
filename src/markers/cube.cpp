// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "markers/cube.h"

int CubeMarker::sides() const { return 6; }

std::vector<Triangle> CubeMarker::makeCube(const Vec3<float> centre, float thickness) const
{
    std::vector<Triangle> ts(12);

    Quad t;
    t = Quad(centre, centre, centre, centre);
    t = t - zhat * thickness;
    t.a -= (xhat + yhat) * thickness;
    t.b += (xhat - yhat) * thickness;
    t.c += (xhat + yhat) * thickness;
    t.d -= (xhat - yhat) * thickness;
    {
        auto [first, second] = t.asTriangles();
        ts[0] = first;
        ts[1] = second;
    }

    t = Quad(centre, centre, centre, centre);
    t = t + zhat * thickness;
    t.a -= (xhat + yhat) * thickness;
    t.b += (xhat - yhat) * thickness;
    t.c += (xhat + yhat) * thickness;
    t.d -= (xhat - yhat) * thickness;
    {
        auto [first, second] = t.flip().asTriangles();
        ts[2] = first;
        ts[3] = second;
    }

    t = Quad(centre, centre, centre, centre);
    t = t + xhat * thickness;
    t.a -= (zhat + yhat) * thickness;
    t.b += (zhat - yhat) * thickness;
    t.c += (zhat + yhat) * thickness;
    t.d -= (zhat - yhat) * thickness;
    {
        auto [first, second] = t.asTriangles();
        ts[4] = first;
        ts[5] = second;
    }

    t = Quad(centre, centre, centre, centre);
    t = t - xhat * thickness;
    t.a -= (zhat + yhat) * thickness;
    t.b += (zhat - yhat) * thickness;
    t.c += (zhat + yhat) * thickness;
    t.d -= (zhat - yhat) * thickness;
    {
        auto [first, second] = t.flip().asTriangles();
        ts[6] = first;
        ts[7] = second;
    }

    t = Quad(centre, centre, centre, centre);
    t = t + yhat * thickness;
    t.a -= (xhat + zhat) * thickness;
    t.b += (xhat - zhat) * thickness;
    t.c += (xhat + zhat) * thickness;
    t.d -= (xhat - zhat) * thickness;
    {
        auto [first, second] = t.asTriangles();
        ts[8] = first;
        ts[9] = second;
    }

    t = Quad(centre, centre, centre, centre);
    t = t - yhat * thickness;
    t.a -= (xhat + zhat) * thickness;
    t.b += (xhat - zhat) * thickness;
    t.c += (xhat + zhat) * thickness;
    t.d -= (xhat - zhat) * thickness;
    {
        auto [first, second] = t.flip().asTriangles();
        ts[10] = first;
        ts[11] = second;
    }

    return ts;
}
