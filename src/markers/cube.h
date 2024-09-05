// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "markers/marker.h"

class CubeMarker
{
    public:
    CubeMarker();
    static std::vector<Triangle> makeCube(const Vec3<float> centre, float thickness);
    static int sides();
};
