#pragma once

#include "axis.h"
#include "triangle.h"
#include <QQuick3DGeometry>
#include <QVector3D>
#include <vector>

class PlotGeometry : public QQuick3DGeometry
{
    Q_OBJECT
    Q_PROPERTY(double thickness MEMBER thickness_ NOTIFY dataChanged)
    Q_PROPERTY(QList<double> xs MEMBER xs_ NOTIFY dataChanged)
    Q_PROPERTY(QList<double> ys MEMBER ys_ NOTIFY dataChanged)
    Q_PROPERTY(Axis *xAxis MEMBER xAxis_ NOTIFY dataChanged)
    Q_PROPERTY(Axis *yAxis MEMBER yAxis_ NOTIFY dataChanged)

    Q_SIGNALS:
    void dataChanged();

    protected:
    PlotGeometry();
    virtual std::vector<Triangle> faces_(std::vector<Point> points) const;
    void updateData();
    double thickness_ = 0.01;
    QList<double> xs_, ys_;
    Axis *xAxis_, *yAxis_;
};
