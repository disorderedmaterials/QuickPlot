#pragma once

#include <QVector3D>
#include <QQuick3DGeometry>
#include "axisTickLabels.h"

class Axis : public QQuick3DGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Axis)
    Q_PROPERTY(double thickness MEMBER thickness_ NOTIFY dataChanged)
    Q_PROPERTY(double minimum MEMBER minimum_ NOTIFY dataChanged)
    Q_PROPERTY(double maximum MEMBER maximum_ NOTIFY dataChanged)
    Q_PROPERTY(bool direction MEMBER direction_ NOTIFY dataChanged)
    Q_PROPERTY(AxisTickLabels* tickLabels READ tickLabels NOTIFY dataChanged)
    Q_PROPERTY(int tickCount READ tickCount WRITE setTickCount)

public:
    Axis();
    std::vector<float> convert(QList<double> values);
    AxisTickLabels* tickLabels();
    bool direction() const;
    double minimum() const;
    double maximum() const;
    int tickCount() const;
    void setTickCount(const int count);

Q_SIGNALS:
  void dataChanged();

private:
    void updateData();
    bool direction_;
    double minimum_, maximum_, thickness_;
    AxisTickLabels tickLabels_;
};
