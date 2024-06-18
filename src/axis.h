#pragma once

#include "axisTickLabels.h"
#include <QQuick3DGeometry>
#include <QVector3D>

class Axis : public QQuick3DGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Axis)
    Q_PROPERTY(double thickness MEMBER thickness_ NOTIFY dataChanged)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY dataChanged)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY dataChanged)
    Q_PROPERTY(bool direction MEMBER direction_ NOTIFY dataChanged)
    Q_PROPERTY(AxisTickLabels *tickLabels READ tickLabels NOTIFY dataChanged)
    Q_PROPERTY(int tickCount READ tickCount NOTIFY dataChanged)

    public:
    Axis();
    virtual std::vector<float> convert(QList<double> values) const;
    AxisTickLabels *tickLabels();
    bool direction() const;
    double minimum() const;
    void setMinimum(const double value);
    double maximum() const;
    void setMaximum(const double value);
    int tickCount() const;
    double tick(int index) const;
    virtual double tickCoord(int index) const;

    Q_SIGNALS:
    void dataChanged();

    public slots:
    virtual void nudge(double delta);

    protected:
    std::vector<double> tics_;
    double minimum_, maximum_;

    private:
    virtual void updateTicks_();
    void updateData();
    bool direction_;
    double thickness_;
    AxisTickLabels tickLabels_;
};
