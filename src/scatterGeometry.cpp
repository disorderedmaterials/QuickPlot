#include "scatterGeometry.h"
#include "triangle.h"
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

    std::vector<Point> ps(N);
    for (int i = 0; i < N; i++)
    {
        ps[i] = Point(xs[i], ys[i], 0.0);
    }

    std::vector<Triangle> ts(2 * N);
    for (int i = 0; i < N; i++)
    {
        Triangle t(ps[i], ps[i], ps[i]);
        t.a.x -= thickness_;
        t.a.y -= thickness_;
        t.b.x += thickness_;
        t.b.y -= thickness_;
        t.c.x += thickness_;
        t.c.y += thickness_;
        ts[2 * i] = t;

        t = Triangle(ps[i], ps[i], ps[i]);
        t.a.x -= thickness_;
        t.a.y -= thickness_;
        t.b.x += thickness_;
        t.b.y += thickness_;
        t.c.x -= thickness_;
        t.c.y += thickness_;
        ts[2 * i + 1] = t;
    }

    for (auto &t : ts)
    {
        p = t.writeByteArray(p);
    }

    setVertexData(vertexData);
    setStride(stride);
    setBounds(QVector3D(-1.0f, -1.0f, 0.0f), QVector3D(+1.0f, +1.0f, 0.0f));

    // setPrimitiveType(QQuick3DGeometry::PrimitiveType::TriangleStrip);

    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic, 0, QQuick3DGeometry::Attribute::F32Type);

    update();
}
