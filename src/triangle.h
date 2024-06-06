#pragma once

class Point
{
    public:
    Point(float a = 0.0, float b = 0.0, float c = 0.0);
    float x, y, z;
};

class Triangle
{
    public:
    Triangle(Point i = 0.0, Point j = 0.0, Point k = 0.0);
    Point a, b, c;
    float *writeByteArray(float *p);
};
