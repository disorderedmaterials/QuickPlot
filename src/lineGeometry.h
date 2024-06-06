#pragma once

#include "axis.h"
#include "plotGeometry.h"
#include <QVector3D>

class LineGeometry : public PlotGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(LineGeometry)
    Q_PROPERTY(double thickness MEMBER thickness_ NOTIFY dataChanged)
    Q_PROPERTY(QList<double> xs MEMBER xs_ NOTIFY dataChanged)
    Q_PROPERTY(QList<double> ys MEMBER ys_ NOTIFY dataChanged)
    Q_PROPERTY(Axis *xAxis MEMBER xAxis_ NOTIFY dataChanged)
    Q_PROPERTY(Axis *yAxis MEMBER yAxis_ NOTIFY dataChanged)

    Q_SIGNALS:
    void dataChanged();

    public:
    LineGeometry();

    private:
    std::vector<Triangle> faces_(std::vector<Point> points) const override;
};
