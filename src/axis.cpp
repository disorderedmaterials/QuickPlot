// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "axis.h"
#include <algorithm>

#include "vector3.h"
#include <cmath>
#include <iostream>

const Vec3<float> xhat = Vec3<float>{1, 0, 0};
const Vec3<float> yhat = Vec3<float>{0, 1, 0};
const Vec3<float> zhat = Vec3<float>{0, 0, 1};

Axis::Axis() : minimum_(-1), maximum_(1), direction_(Axis::Direction::Y), thickness_(0.001), tickLabels_(*this)
{
    updateData();
    connect(this, &Axis::dataChanged, this, &Axis::updateData);
}

AxisTickLabels *Axis::tickLabels() { return &tickLabels_; }

Axis::Direction Axis::direction() const { return direction_; }
double Axis::minimum() const { return minimum_; }
void Axis::setMinimum(const double value) { minimum_ = value; }
double Axis::maximum() const { return maximum_; }
void Axis::setMaximum(const double value) { maximum_ = value; }

int Axis::tickCount() const { return tics_.size(); }

void Axis::updateTicks_()
{

    auto full_diff = maximum_ - minimum_;
    auto diff = pow(10.0, floor(log(full_diff) / log(10.0)));
    while (full_diff / diff < 4)
    {
        diff /= 2;
    }
    while (full_diff / diff > 9)
    {
        diff *= 2;
    }
    tics_.clear();

    auto current = floor(minimum_ / diff) * diff;

    while (current < minimum_)
        current += diff;

    while (current <= maximum_)
    {
        tics_.emplace_back(current);
        current += diff;
    }
}

float *draw_tube(float *p, float thickness, Vec3<float> v1, Vec3<float> v2, Vec3<float> n1, Vec3<float> n2)
{
    // -n1
    p = (v1 - (n1 + n2) * thickness).write(p);
    p = (v1 - (n1 - n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);

    p = (v2 - (n1 - n2) * thickness).write(p);
    p = (v2 - (n1 + n2) * thickness).write(p);
    p = (v1 - (n1 + n2) * thickness).write(p);

    // +n1
    p = (v1 + (n1 + n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);
    p = (v2 + (n1 - n2) * thickness).write(p);

    p = (v2 + (n1 - n2) * thickness).write(p);
    p = (v2 + (n1 + n2) * thickness).write(p);
    p = (v1 + (n1 + n2) * thickness).write(p);

    // +n2
    p = (v1 - (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);

    p = (v2 + (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 + n2) * thickness).write(p);

    // // -n2
    p = (v1 + (n1 - n2) * thickness).write(p);
    p = (v1 - (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 + n2) * thickness).write(p);

    p = (v2 - (n1 + n2) * thickness).write(p);
    p = (v2 + (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);

    // v1 cap
    p = (v1 - (n1 + n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);
    p = (v1 - (n1 - n2) * thickness).write(p);

    p = (v1 + (n1 + n2) * thickness).write(p);
    p = (v1 - (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);

    // v2 cap
    p = (v2 + (n1 - n2) * thickness).write(p);
    p = (v2 - (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);

    p = (v2 - (n1 - n2) * thickness).write(p);
    p = (v2 + (n1 + n2) * thickness).write(p);
    p = (v2 + (n1 - n2) * thickness).write(p);

    return p;
}

void Axis::updateData()
{
    clear();

    updateTicks_();
    tickLabels_.reset();

    int stride = 3 * sizeof(float);

    QByteArray vertexData(6 * 6 * stride, Qt::Initialization::Uninitialized);
    float *p = reinterpret_cast<float *>(vertexData.data());

    switch (direction_)
    {
        case Axis::Direction::X:
            draw_tube(p, thickness_, Vec3<float>{-1.0f - (float)thickness_, -1.0, 0},
                      Vec3<float>{1.0f + (float)thickness_, -1.0, 0}, yhat, zhat);
            break;
        case Axis::Direction::Y:
            draw_tube(p, thickness_, Vec3<float>{-1.0, -1.0f - (float)thickness_, 0},
                      Vec3<float>{-1.0, 1.0f + (float)thickness_, 0}, zhat, xhat);
            break;
        case Axis::Direction::Z:
            draw_tube(p, thickness_, Vec3<float>{-1.0, -1.0, 0.0f - (float)thickness_},
                      Vec3<float>{-1.0, -1.0, 4.0f + (float)thickness_}, xhat, yhat);
            break;
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

double Axis::tick(int index) const { return tics_[index]; }

double Axis::tickCoord(int index) const { return 2.0 * (tics_[index] - minimum_) / (maximum_ - minimum_); }

void Axis::nudge(double delta)
{
    minimum_ += delta;
    maximum_ += delta;
    Q_EMIT(dataChanged());
}
