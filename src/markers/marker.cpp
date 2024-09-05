// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "marker.h"
#include "cube.h"
#include "diamond.h"

int markerSides(MarkerType type)
{
    switch (type)
    {
        case MarkerType::Diamond:
            return DiamondMarker::sides();
        case MarkerType::Cube:
        default:
            return CubeMarker::sides();
    }
}

std::vector<Triangle> makeMarker(MarkerType type, const Vec3<float> centre, float thickness)
{
    switch (type)
    {
        case MarkerType::Diamond:
            return DiamondMarker::makeDiamond(centre, thickness);
        case MarkerType::Cube:
        default:
            return CubeMarker::makeCube(centre, thickness);
    }
}
