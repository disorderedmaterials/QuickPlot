// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "scatterGeometry.h"
#include "markers/marker.h"
#include "triangle.h"
#include <algorithm>

ScatterGeometry::ScatterGeometry() : PlotGeometry() {}

std::vector<Triangle> ScatterGeometry::faces_(std::vector<Vec3<float>> ps) const
{
    const int N = ps.size();

    const int SIDES = markerSides(marker_);

    std::vector<Triangle> ts(SIDES * N);
    for (int i = 0; i < N; i++)
    {
        auto faces = makeMarker(marker_, ps[i], thickness_);
        std::copy(faces.begin(), faces.end(), ts.begin() + SIDES * i);
    }

    return ts;
}
