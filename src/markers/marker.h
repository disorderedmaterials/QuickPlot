// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "triangle.h"

#include <vector>

class Marker
{
    virtual std::vector<Triangle> makeCube(const Vec3<float> centre, float thickness) const;
    virtual int sides() const;
};
