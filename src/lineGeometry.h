// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include "axis.h"
#include "plotGeometry.h"

/** A geometry that draws a line between data points. \todo Convert
    from a line to a rectangular tube to be more visible in three
    dimesions */
class LineGeometry : public PlotGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(LineGeometry)

    public:
    LineGeometry();

    private:
    std::vector<Triangle> faces_(std::vector<Point> points) const override;
};
