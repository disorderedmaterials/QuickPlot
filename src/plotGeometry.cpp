// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "plotGeometry.h"

PlotGeometry::PlotGeometry() : xAxis_(nullptr), yAxis_(nullptr)
{
    connect(this, &PlotGeometry::dataChanged, this, &PlotGeometry::updateData);
}

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

    auto ts = clip(faces_(ps));

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

bool outOfBounds(const Point &p) { return p.x < -1 || p.x > 1 || p.y < -1 || p.y > 1 || p.z < -1 || p.z > 1; }

/** A line segment between two vertices of a polygon */
struct Edge
{
    /** The beginning point of the edge */
    Point start;
    /** The stopping point of the edge */
    Point end;
};

std::optional<Edge> clipEdge(const Edge &e)
{
    // Check if edge is entirely in within bounds
    if ((e.start.x > -1 && e.start.x < 1) && (e.end.x > -1 && e.end.x < 1) && (e.start.y > -1 && e.start.y < 1) &&
        (e.end.y > -1 && e.end.y < 1) && (e.start.z > -1 && e.start.z < 1) && (e.end.z > -1 && e.end.z < 1))
        return e;

    // Check if the entire edge is out of bounds
    if ((e.start.x < -1 && e.end.x < -1) || (e.start.x > 1 && e.end.x > 1))
        return {};
    if ((e.start.y < -1 && e.end.y < -1) || (e.start.y > 1 && e.end.y > 1))
        return {};
    if ((e.start.z < -1 && e.end.z < -1) || (e.start.z > 1 && e.end.z > 1))
        return {};

    Edge result = e;

    // Bound to x axis
    if (result.start.x < -1)
    {
        auto alpha = (-1 - result.start.x) / (result.end.x - result.start.x);
        result.start.x = -1;
        result.start.y += alpha * (result.end.y - result.start.y);
        result.start.z += alpha * (result.end.z - result.start.z);
    }
    if (result.end.x < -1)
    {
        auto alpha = (-1 - result.end.x) / (result.end.x - result.start.x);
        result.end.x = -1;
        result.end.y += alpha * (result.end.y - result.start.y);
        result.start.z += alpha * (result.end.z - result.start.z);
    }
    if (result.start.x > 1)
    {
        auto alpha = (1 - result.start.x) / (result.end.x - result.start.x);
        result.start.x = 1;
        result.start.y += alpha * (result.end.y - result.start.y);
        result.start.z += alpha * (result.end.z - result.start.z);
    }
    if (result.end.x > 1)
    {
        auto alpha = (1 - result.end.x) / (result.end.x - result.start.x);
        result.end.x = 1;
        result.end.y += alpha * (result.end.y - result.start.y);
        result.start.z += alpha * (result.end.z - result.start.z);
    }

    // Bound to y axis
    if (result.start.y < -1)
    {
        auto alpha = (-1 - result.start.y) / (result.end.y - result.start.y);
        result.start.y = -1;
        result.start.x += alpha * (result.end.x - result.start.x);
        result.start.z += alpha * (result.end.z - result.start.z);
    }
    if (result.end.y < -1)
    {
        auto alpha = (-1 - result.end.y) / (result.end.y - result.start.y);
        result.end.y = -1;
        result.end.x += alpha * (result.end.x - result.start.x);
        result.start.z += alpha * (result.end.z - result.start.z);
    }
    if (result.start.y > 1)
    {
        auto alpha = (1 - result.start.y) / (result.end.y - result.start.y);
        result.start.y = 1;
        result.start.x += alpha * (result.end.x - result.start.x);
        result.start.z += alpha * (result.end.z - result.start.z);
    }
    if (result.end.y > 1)
    {
        auto alpha = (1 - result.end.y) / (result.end.y - result.start.y);
        result.end.y = 1;
        result.end.x += alpha * (result.end.x - result.start.x);
        result.start.z += alpha * (result.end.z - result.start.z);
    }

    // Bound to z axis
    if (result.start.z < -1)
    {
        auto alpha = (-1 - result.start.z) / (result.end.z - result.start.z);
        result.start.z = -1;
        result.start.x += alpha * (result.end.x - result.start.x);
        result.start.y += alpha * (result.end.y - result.start.y);
    }
    if (result.end.z < -1)
    {
        auto alpha = (-1 - result.end.z) / (result.end.z - result.start.z);
        result.end.z = -1;
        result.end.x += alpha * (result.end.x - result.start.x);
        result.start.y += alpha * (result.end.y - result.start.y);
    }
    if (result.start.z > 1)
    {
        auto alpha = (1 - result.start.z) / (result.end.z - result.start.z);
        result.start.z = 1;
        result.start.x += alpha * (result.end.x - result.start.x);
        result.start.y += alpha * (result.end.y - result.start.y);
    }
    if (result.end.z > 1)
    {
        auto alpha = (1 - result.end.z) / (result.end.z - result.start.z);
        result.end.z = 1;
        result.end.x += alpha * (result.end.x - result.start.x);
        result.start.y += alpha * (result.end.y - result.start.y);
    }

    return result;
}

std::vector<Triangle> PlotGeometry::clip(const std::vector<Triangle> &ts) const
{
    std::vector<Triangle> result;

    for (const auto &t : ts)
    {
        std::vector<Edge> edges = {{t.a, t.b}, {t.b, t.c}, {t.c, t.a}};
        std::vector<Point> vertices;
        for (const auto &e : edges)
        {
            const auto clipped = clipEdge(e);
            if (clipped)
            {
                if (vertices.empty() || vertices.back() != clipped->start)
                    vertices.push_back(clipped->start);
                vertices.push_back(clipped->end);
            }
        }
        if (vertices.empty())
            continue;
        if (vertices.back() == vertices.front())
            vertices.pop_back();
        if (vertices.size() < 3)
            continue;
        for (long unsigned int i = 1; i < vertices.size() - 1; ++i)
            result.emplace_back(vertices[0], vertices[i], vertices[i + 1]);
    }
    return result;
}
