#include "axis.h"
#include <algorithm>

#include <iostream>

Axis::Axis() : direction_(false), minimum_(-1), maximum_(1), thickness_(0.001), tickLabels_(*this)
{
    updateData();
    connect(this, &Axis::dataChanged, this, &Axis::updateData);
}

AxisTickLabels *Axis::tickLabels() { return &tickLabels_; }

bool Axis::direction() const { return direction_; }
double Axis::minimum() const { return minimum_; }
double Axis::maximum() const { return maximum_; }

int Axis::tickCount() const { return tickLabels_.tickCount(); }

void Axis::setTickCount(const int count) { tickLabels_.setTickCount(count); }

void Axis::updateData()
{
    clear();

    int stride = 3 * sizeof(float);

    QByteArray vertexData(6 * stride, Qt::Initialization::Uninitialized);
    float *p = reinterpret_cast<float *>(vertexData.data());

    if (direction_)
    {
        *p++ = -1.0;
        *p++ = -1.0 - thickness_;
        *p++ = 0;
        *p++ = 1.0;
        *p++ = -1.0 - thickness_;
        *p++ = 0;
        *p++ = 1.0;
        *p++ = -1.0 + thickness_;
        *p++ = 0;

        *p++ = 1.0;
        *p++ = -1.0 + thickness_;
        *p++ = 0;
        *p++ = -1.0;
        *p++ = -1.0 + thickness_;
        *p++ = 0;
        *p++ = -1.0;
        *p++ = -1.0 - thickness_;
        *p++ = 0;
    }
    else
    {
        *p++ = -1.0 - thickness_;
        *p++ = -1.0;
        *p++ = 0;
        *p++ = -1.0 + thickness_;
        *p++ = 1.0;
        *p++ = 0;
        *p++ = -1.0 - thickness_;
        *p++ = 1.0;
        *p++ = 0;

        *p++ = -1.0 - thickness_;
        *p++ = -1.0;
        *p++ = 0;
        *p++ = -1.0 + thickness_;
        *p++ = -1.0;
        *p++ = 0;
        *p++ = -1.0 + thickness_;
        *p++ = 1.0;
        *p++ = 0;
    }

    setVertexData(vertexData);
    setStride(stride);
    setBounds(QVector3D(-1.0f - thickness_, -1.0f - thickness_, 0.0f), QVector3D(1.0f + thickness_, 1.0f + thickness_, 0.0f));

    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic, 0, QQuick3DGeometry::Attribute::F32Type);

    update();
}

std::vector<float> Axis::convert(QList<double> points) const
{
    std::vector<float> result(points.length());

    std::transform(points.begin(), points.end(), result.begin(),
                   [this](const auto x) { return -1.0f + 2 * (x - minimum_) / (maximum_ - minimum_); });

    return result;
}

double Axis::tick(int index, int count) const {
  return minimum_ + (double) index / ((double) count - 1.0) * (maximum_ - minimum_);
}
