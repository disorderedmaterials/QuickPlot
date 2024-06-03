#pragma once

#include "axis.h"
#include "axisTickLabels.h"
#include <QQuick3DGeometry>
#include <QVector3D>

class LogAxis : public Axis
{
    Q_OBJECT
    QML_NAMED_ELEMENT(LogAxis)

    public:
    LogAxis();
    std::vector<float> convert(QList<double> values) const override;
    double tick(int index) const override;

    Q_SIGNALS:
    void dataChanged();
};
