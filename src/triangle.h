// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include "vector3.h"

/** A line segment between two vertices of a polygon */
class Edge
{
    public:
    /** The beginning point of the edge */
    Vec3<float> start;
    /** The stopping point of the edge */
    Vec3<float> end;
    /** Treat two edges as the corners of a bounding box and return
        the bouning box of their union. */
    Edge combine(const Edge &other) const;
};

/** An individual triangle face in the mesh.  */
class Triangle
{
    public:
    Triangle(Vec3<float> i = 0.0f, Vec3<float> j = 0.0f, Vec3<float> k = 0.0f);
    /** @name Vertices
        The vertices of the triangle */
    /**@{ A vertex of the triangle */
    Vec3<float> a, b, c;
    /**@} */
    /** Write the triangle into a vertex buffer

        @param p A pointer into the vertex buffer.  The buffer must
        have enough space to write the vertex.
     */
    float *writeByteArray(float *p);
    /** find the bounding box of the triangle and return as the diagonal from min to max */
    Edge bounds() const;
};
