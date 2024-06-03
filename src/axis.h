#pragma once

#include "axisTickLabels.h"
#include <QQuick3DGeometry>
#include <QVector3D>

class Axis : public QQuick3DGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Axis)
    Q_PROPERTY(double thickness MEMBER thickness_ NOTIFY dataChanged)
    Q_PROPERTY(double minimum MEMBER minimum_ NOTIFY dataChanged)
    Q_PROPERTY(double maximum MEMBER maximum_ NOTIFY dataChanged)
    Q_PROPERTY(bool direction MEMBER direction_ NOTIFY dataChanged)
    Q_PROPERTY(AxisTickLabels *tickLabels READ tickLabels NOTIFY dataChanged)
    Q_PROPERTY(int tickCount READ tickCount NOTIFY dataChanged)

    public:
    Axis();
    virtual std::vector<float> convert(QList<double> values) const;
    AxisTickLabels *tickLabels();
    bool direction() const;
    double minimum() const;
    double maximum() const;
    int tickCount() const;
    virtual double tick(int index) const;
    virtual double tickCoord(int index) const;

    Q_SIGNALS:
    void dataChanged();

    private:
    void updateData();
    bool direction_;
    double minimum_, maximum_, thickness_;
    AxisTickLabels tickLabels_;
    std::vector<double> tics_;
};
