// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "triangle.h"
#include <algorithm>

Point::Point(float a, float b, float c) : x(a), y(b), z(c) {}

bool Point::operator==(const Point &other) { return x == other.x && y == other.y && z == other.z; }
bool Point::operator!=(const Point &other) { return x != other.x || y != other.y || z != other.z; }

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

Triangle::Triangle(Point i, Point j, Point k) : a(i), b(j), c(k) {}

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
    *p++ = a.x;
    *p++ = a.y;
    *p++ = a.z;

    *p++ = b.x;
    *p++ = b.y;
    *p++ = b.z;

    *p++ = c.x;
    *p++ = c.y;
    *p++ = c.z;

    return p;
}
