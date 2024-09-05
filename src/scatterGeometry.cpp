// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "scatterGeometry.h"
#include "markers/cube.h"
#include "triangle.h"
#include <algorithm>

ScatterGeometry::ScatterGeometry() : PlotGeometry() {}

std::vector<Triangle> ScatterGeometry::faces_(std::vector<Vec3<float>> ps) const
{
    const int N = ps.size();

    const int SIDES = CubeMarker::sides();

    std::vector<Triangle> ts(SIDES * N);
    for (int i = 0; i < N; i++)
    {
        auto faces = CubeMarker::makeCube(ps[i], thickness_);
        std::copy(faces.begin(), faces.end(), ts.begin() + SIDES * i);
    }

    return ts;
}
