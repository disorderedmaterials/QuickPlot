// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include "axis.h"
#include "triangle.h"
#include <QQuick3DGeometry>
#include <QVector3D>
#include <vector>

/** The base class for drawing data points on the plot */
class PlotGeometry : public QQuick3DGeometry
{
    Q_OBJECT
    /** The width of the data point drawing */
    Q_PROPERTY(double thickness MEMBER thickness_ NOTIFY dataChanged)
    /** The X coordinates of the data points in data space */
    Q_PROPERTY(QList<double> xs MEMBER xs_ NOTIFY dataChanged)
    /** The Y coordinates of the data points in data space */
    Q_PROPERTY(QList<double> ys MEMBER ys_ NOTIFY dataChanged)
    /** The X axis that the data is plotted against */
    Q_PROPERTY(Axis *xAxis MEMBER xAxis_ NOTIFY dataChanged)
    /** The Y axis that the data is plotted against */
    Q_PROPERTY(Axis *yAxis MEMBER yAxis_ NOTIFY dataChanged)

    Q_SIGNALS:
    /** The signal that is thrown when the data points have changed position in chart space */
    void dataChanged();

    protected:
    PlotGeometry();
    /** An array of polygon faces that would plot the given data
        points.  The points should be in chart space (not data
        space).*/
    virtual std::vector<Triangle> faces_(std::vector<Vec3<float>> points) const;
    /** Take a list of polygon faces and crop them so that nothing
        extends outside of the charting space.  Triangles completely
        outside the region are dropped while triangles partially
        within the region are converted into a group of polygons
        completely inside the bounds. */
    std::vector<Triangle> clip(const std::vector<Triangle> &ts) const;
    /** Present the latest geometry to the renderer */
    void updateData();
    /** The size of the plotting geometry */
    double thickness_ = 0.01;
    /** @name Data
        The coordinates in data space of the data points */
    /**@{ The coordinates of the data point along this axis */
    QList<double> xs_, ys_;
    /**@}*/
    /** @name Axes
        Pointers to the axes used to plot the data */
    /**@{ The axes along which the data are plotted */
    Axis *xAxis_, *yAxis_;
    /**@} */
};
