#include "lineGeometry.h"
#include "triangle.h"
#include <algorithm>

LineGeometry::LineGeometry() : PlotGeometry() { connect(this, &LineGeometry::dataChanged, this, &LineGeometry::updateData); }

std::vector<Triangle> LineGeometry::faces_(std::vector<Point> ps) const
{
    const int N = ps.size();

    std::vector<float> angles(N);
    // Calculate derivatives
    for (int i = 1; i < N - 1; ++i)
    {
        auto angle = atan2(ps[i + 1].y - ps[i - 1].y, ps[i + 1].x - ps[i - 1].x);
        angles[i] = angle + M_PI / 2;
    }
    angles[0] = M_PI / 2 + atan2(ps[1].y - ps[0].y, ps[1].x - ps[0].x);
    angles[N - 1] = M_PI / 2 + atan2(ps[N - 1].y - ps[N - 2].y, ps[N - 1].x - ps[N - 2].x);

    std::vector<Triangle> ts(2 * N);

    for (int i = 0; i < N - 1; i++)
    {
        Triangle t(ps[i], ps[i], ps[i + 1]);
        t.a.x += cos(angles[i]) * thickness_;
        t.a.y += sin(angles[i]) * thickness_;
        t.b.x -= cos(angles[i]) * thickness_;
        t.b.y -= sin(angles[i]) * thickness_;
        t.c.x -= cos(angles[i + 1]) * thickness_;
        t.c.y -= sin(angles[i + 1]) * thickness_;
        ts[2 * i] = t;

        t = Triangle(ps[i + 1], ps[i + 1], ps[i]);
        t.a.x -= cos(angles[i + 1]) * thickness_;
        t.a.y -= sin(angles[i + 1]) * thickness_;
        t.b.x += cos(angles[i + 1]) * thickness_;
        t.b.y += sin(angles[i + 1]) * thickness_;
        t.c.x += cos(angles[i]) * thickness_;
        t.c.y += sin(angles[i]) * thickness_;
        ts[2 * i + 1] = t;
    }

    return ts;
}
