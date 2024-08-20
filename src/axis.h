// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include "axisTickLabels.h"
#include <QQuick3DGeometry>
#include <QVector3D>

/** A translation between data values and graph coordinates */
class Axis : public QQuick3DGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Axis)
    Q_PROPERTY(double thickness MEMBER thickness_ NOTIFY dataChanged)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY dataChanged)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY dataChanged)
    Q_PROPERTY(Direction direction MEMBER direction_ NOTIFY dataChanged)
    Q_PROPERTY(AxisTickLabels *tickLabels READ tickLabels NOTIFY dataChanged)
    Q_PROPERTY(int tickCount READ tickCount NOTIFY dataChanged)

    public:
    Axis();

    enum Direction
    {
        Y,
        X
    };
    Q_ENUMS(Direction)

    /** Translate data space values into plot space values.
        Subclasses will overload this method to enable different
        scaling methods (e.g. log scaling). */
    virtual std::vector<float> convert(QList<double> values) const;

    /** The tick label model for this axis */
    AxisTickLabels *tickLabels();

    /** The direction in which the axis is pointing. \todo This needs
        to be a proper enum to handle three dimensions */
    bool direction() const;
    /** Get the minimum edge of the axis */
    double minimum() const;
    /** Set the minimum edge of the axis */
    void setMinimum(const double value);
    /** Get the maximum edge of the axis */
    double maximum() const;
    /** Set the maximum edge of the axis */
    void setMaximum(const double value);
    /** The number of tick labels on the axis */
    int tickCount() const;
    /** Access the value of an individual tick label by index */
    double tick(int index) const;
    /** Access the position of an individual tick label by index */
    virtual double tickCoord(int index) const;

    Q_SIGNALS:
    void dataChanged();

    public Q_SLOTS:
    /** Shift the axis bounds by a given distance */
    virtual void nudge(double delta);

    protected:
    /** The tick labels values */
    std::vector<double> tics_;
    double minimum_, maximum_;

    private:
    /** Update the labels of the tick labels */
    virtual void updateTicks_();
    /** Update the axis display in response to changes in the data.*/
    void updateData();
    Direction direction_;
    /** The line thickness of the axis */
    double thickness_;
    AxisTickLabels tickLabels_;
};
