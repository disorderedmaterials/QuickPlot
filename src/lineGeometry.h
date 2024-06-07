#pragma once

#include "axis.h"
#include "plotGeometry.h"

class LineGeometry : public PlotGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(LineGeometry)

    public:
    LineGeometry();

    private:
    std::vector<Triangle> faces_(std::vector<Point> points) const override;
};
