// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

/** An individual point in 3D space. */
class Point
{
    public:
    /** A constructor that accepts the individual coordinates) */
    Point(float a = 0.0, float b = 0.0, float c = 0.0);
    /** @name Coordinates
        The location of the point */
    /**@{ The coordinate position */
    float x, y, z;
    /**@} */
    bool operator==(const Point &other);
    bool operator!=(const Point &other);
};

/** A line segment between two vertices of a polygon */
class Edge
{
    public:
    /** The beginning point of the edge */
    Point start;
    /** The stopping point of the edge */
    Point end;
    /** Treat two edges as the corners of a bounding box and return
        the bouning box of their union. */
    Edge combine(const Edge &other) const;
};

/** An individual triangle face in the mesh.  */
class Triangle
{
    public:
    Triangle(Point i = 0.0, Point j = 0.0, Point k = 0.0);
    /** @name Vertices
        The vertices of the triangle */
    /**@{ A vertex of the triangle */
    Point a, b, c;
    /**@} */
    /** Write the triangle into a vertex buffer

        @param p A pointer into the vertex buffer.  The buffer must
        have enough space to write the vertex.
     */
    float *writeByteArray(float *p);
    /** find the bounding box of the triangle and return as the diagonal from min to max */
    Edge bounds() const;
};
