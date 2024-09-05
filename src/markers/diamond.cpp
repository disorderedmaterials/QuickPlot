// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "markers/diamond.h"

DiamondMarker::DiamondMarker() {}

int DiamondMarker::sides() { return 8; }

std::vector<Triangle> DiamondMarker::makeDiamond(const Vec3<float> centre, float thickness)
{
    std::vector<Triangle> ts(sides());
    Triangle t;

    t = Triangle(centre, centre, centre);
    t.a += yhat * thickness;
    t.b += (xhat + zhat) * thickness;
    t.c += (-xhat + zhat) * thickness;
    ts[0] = t;

    t = Triangle(centre, centre, centre);
    t.a += yhat * thickness;
    t.b += (xhat - zhat) * thickness;
    t.c += (xhat + zhat) * thickness;
    ts[1] = t;

    t = Triangle(centre, centre, centre);
    t.a += yhat * thickness;
    t.b += (-xhat - zhat) * thickness;
    t.c += (xhat - zhat) * thickness;
    ts[2] = t;

    t = Triangle(centre, centre, centre);
    t.a += yhat * thickness;
    t.b += (-xhat + zhat) * thickness;
    t.c += (-xhat - zhat) * thickness;
    ts[3] = t;

    t = Triangle(centre, centre, centre);
    t.a -= yhat * thickness;
    t.b += (-xhat + zhat) * thickness;
    t.c += (xhat + zhat) * thickness;
    ts[4] = t;

    t = Triangle(centre, centre, centre);
    t.a -= yhat * thickness;
    t.b += (xhat + zhat) * thickness;
    t.c += (xhat - zhat) * thickness;
    ts[5] = t;

    t = Triangle(centre, centre, centre);
    t.a -= yhat * thickness;
    t.b += (xhat - zhat) * thickness;
    t.c += (-xhat - zhat) * thickness;
    ts[6] = t;

    t = Triangle(centre, centre, centre);
    t.a -= yhat * thickness;
    t.b += (-xhat - zhat) * thickness;
    t.c += (-xhat + zhat) * thickness;
    ts[7] = t;

    return ts;
}
