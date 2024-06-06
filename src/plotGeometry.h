#pragma once

#include "axis.h"
#include "triangle.h"
#include <QQuick3DGeometry>
#include <QVector3D>
#include <vector>

class PlotGeometry : public QQuick3DGeometry
{
    protected:
    PlotGeometry();
    virtual std::vector<Triangle> faces_(std::vector<Point> points) const;
    void updateData();
    double thickness_ = 0.01;
    QList<double> xs_, ys_;
    Axis *xAxis_, *yAxis_;
};
