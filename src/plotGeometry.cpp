#include "plotGeometry.h"

PlotGeometry::PlotGeometry() : xAxis_(nullptr), yAxis_(nullptr) {}

void PlotGeometry::updateData()
{
    clear();

    const int N = xs_.length();

    // Sanity Checks
    if (N < 2 || ys_.length() < 2)
        return;
    if (!xAxis_)
        return;
    if (!yAxis_)
        return;

    int stride = 3 * sizeof(float);

    auto xs = xAxis_->convert(xs_);
    auto ys = yAxis_->convert(ys_);

    std::vector<Point> ps(N);
    for (int i = 0; i < N; i++)
    {
        ps[i] = Point(xs[i], ys[i], 0.0);
    }

    auto ts = faces_(ps);

    QByteArray vertexData(3 * ts.size() * stride, Qt::Initialization::Uninitialized);
    float *p = reinterpret_cast<float *>(vertexData.data());

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

std::vector<Triangle> PlotGeometry::faces_([[maybe_unused]] std::vector<Point> ps) const { return {}; }
