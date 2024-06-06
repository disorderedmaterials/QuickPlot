#include "triangle.h"

Point::Point(float a, float b, float c) : x(a), y(b), z(c) {}

Triangle::Triangle(Point i, Point j, Point k) : a(i), b(j), c(k) {}

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
