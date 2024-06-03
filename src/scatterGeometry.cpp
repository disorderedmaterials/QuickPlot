#include "scatterGeometry.h"
#include <algorithm>

ScatterGeometry::ScatterGeometry() : xAxis_(nullptr), yAxis_(nullptr)
{
    connect(this, &ScatterGeometry::dataChanged, this, &ScatterGeometry::updateData);
}

void ScatterGeometry::updateData()
{
    clear();

    const int N = xs_.length();

    // Sanity Checks
    if (N < 1 || ys_.length() < 1)
        return;
    if (!xAxis_)
        return;
    if (!yAxis_)
        return;

    int stride = 3 * sizeof(float);

    QByteArray vertexData(6 * N * stride, Qt::Initialization::Uninitialized);
    float *p = reinterpret_cast<float *>(vertexData.data());

    auto xs = xAxis_->convert(xs_);
    auto ys = yAxis_->convert(ys_);

    for (int i = 0; i < N; i++)
    {
        *p++ = xs[i] - thickness_;
        *p++ = ys[i] - thickness_;
        *p++ = 0.0f;
        *p++ = xs[i] + thickness_;
        *p++ = ys[i] - thickness_;
        *p++ = 0.0f;
        *p++ = xs[i] + thickness_;
        *p++ = ys[i] + thickness_;
        *p++ = 0.0f;

        *p++ = xs[i] - thickness_;
        *p++ = ys[i] - thickness_;
        *p++ = 0.0f;
        *p++ = xs[i] + thickness_;
        *p++ = ys[i] + thickness_;
        *p++ = 0.0f;
        *p++ = xs[i] - thickness_;
        *p++ = ys[i] + thickness_;
        *p++ = 0.0f;
    }

    setVertexData(vertexData);
    setStride(stride);
    setBounds(QVector3D(-1.0f, -1.0f, 0.0f), QVector3D(+1.0f, +1.0f, 0.0f));

    // setPrimitiveType(QQuick3DGeometry::PrimitiveType::TriangleStrip);

    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic, 0, QQuick3DGeometry::Attribute::F32Type);

    update();
}
