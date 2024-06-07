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
    double tickCoord(int index) const override;
    void nudge(double delta);

    private:
    void updateTicks_() override;

    Q_SIGNALS:
    void dataChanged();
};
