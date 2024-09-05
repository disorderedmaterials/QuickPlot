// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "markers/marker.h"

class DiamondMarker
{
    public:
    DiamondMarker();
    static std::vector<Triangle> makeDiamond(const Vec3<float> centre, float thickness);
    static int sides();
};
