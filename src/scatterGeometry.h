#pragma once

#include "axis.h"
#include "plotGeometry.h"

class ScatterGeometry : public PlotGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ScatterGeometry)

    public:
    ScatterGeometry();

    private:
    std::vector<Triangle> faces_(std::vector<Point> points) const override;
};
