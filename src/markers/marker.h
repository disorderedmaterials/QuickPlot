// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include "triangle.h"

#include <vector>

enum class MarkerType
{
    Cube,
    Diamond // Really a tetrahedron
};

int markerSides(MarkerType type);

std::vector<Triangle> makeMarker(MarkerType type, const Vec3<float> centre, float thickness);
