// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include "axis.h"
#include "markers/marker.h"
#include "plotGeometry.h"
#include <memory>

/** A plotting style for individual square points on a scatter
    plot. \todo Converts the squares to cubes for better 3D charts. */
class ScatterGeometry : public PlotGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ScatterGeometry)

    public:
    ScatterGeometry();

    private:
    std::vector<Triangle> faces_(std::vector<Vec3<float>> points) const override;
    MarkerType marker_ = MarkerType::Diamond;
};
