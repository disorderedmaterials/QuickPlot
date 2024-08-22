// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "triangle.h"
#include <algorithm>

Edge Edge::combine(const Edge &other) const
{
    Edge result;
    result.start.x = std::min(start.x, other.start.x);
    result.start.y = std::min(start.y, other.start.y);
    result.start.z = std::min(start.z, other.start.z);
    result.end.x = std::max(end.x, other.end.x);
    result.end.y = std::max(end.y, other.end.y);
    result.end.z = std::max(end.z, other.end.z);
    return result;
}

Triangle::Triangle(Vec3<float> i, Vec3<float> j, Vec3<float> k) : a(i), b(j), c(k) {}

Edge Triangle::bounds() const
{
    Edge result;
    result.start.x = std::min({a.x, b.x, c.x});
    result.start.y = std::min({a.y, b.y, c.y});
    result.start.z = std::min({a.z, b.z, c.z});

    result.end.x = std::max({a.x, b.x, c.x});
    result.end.y = std::max({a.y, b.y, c.y});
    result.end.z = std::max({a.z, b.z, c.z});

    return result;
}

float *Triangle::writeByteArray(float *p)
{
    p = a.write(p);
    p = b.write(p);
    p = c.write(p);
    return p;
}

Triangle Triangle::operator+(const Vec3<float> &offset) const
{
    Triangle result;
    result.a = a + offset;
    result.b = b + offset;
    result.c = c + offset;
    return result;
}

Triangle Triangle::operator-(const Vec3<float> &offset) const
{
    Triangle result;
    result.a = a - offset;
    result.b = b - offset;
    result.c = c - offset;
    return result;
}

Triangle Triangle::flip() const { return Triangle(a, c, b); }

Quad::Quad(Vec3<float> i, Vec3<float> j, Vec3<float> k, Vec3<float> l) : a(i), b(j), c(k), d(l) {}

Edge Quad::bounds() const
{
    Edge result;
    result.start.x = std::min({a.x, b.x, c.x, d.x});
    result.start.y = std::min({a.y, b.y, c.y, d.y});
    result.start.z = std::min({a.z, b.z, c.z, d.z});

    result.end.x = std::max({a.x, b.x, c.x, d.x});
    result.end.y = std::max({a.y, b.y, c.y, d.y});
    result.end.z = std::max({a.z, b.z, c.z, d.z});

    return result;
}

float *Quad::writeByteArray(float *p)
{
    p = a.write(p);
    p = b.write(p);
    p = c.write(p);

    p = c.write(p);
    p = d.write(p);
    p = a.write(p);

    return p;
}

Quad Quad::operator+(const Vec3<float> &offset) const
{
    Quad result;
    result.a = a + offset;
    result.b = b + offset;
    result.c = c + offset;
    result.d = d + offset;
    return result;
}

Quad Quad::operator-(const Vec3<float> &offset) const
{
    Quad result;
    result.a = a - offset;
    result.b = b - offset;
    result.c = c - offset;
    result.d = d - offset;
    return result;
}

Quad Quad::flip() const { return Quad(a, d, c, b); }
