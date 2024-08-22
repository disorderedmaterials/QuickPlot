#include "solid.h"
#include "triangle.h"

float *draw_tube(float *p, float thickness, Vec3<float> v1, Vec3<float> v2, Vec3<float> n1, Vec3<float> n2)
{

    Quad q;
    q = Quad(v1 - (n1 + n2) * thickness, v1 - (n1 - n2) * thickness, v2 - (n1 - n2) * thickness, v2 - (n1 + n2) * thickness);
    p = q.writeByteArray(p);

    q = Quad(v1 + (n1 - n2) * thickness, v1 + (n1 + n2) * thickness, v2 + (n1 + n2) * thickness, v2 + (n1 - n2) * thickness);
    p = q.flip().writeByteArray(p);

    q = Quad(v1 - (n2 + n1) * thickness, v1 - (n2 - n1) * thickness, v2 - (n2 - n1) * thickness, v2 - (n2 + n1) * thickness);
    p = q.flip().writeByteArray(p);

    q = Quad(v1 + (n2 - n1) * thickness, v1 + (n2 + n1) * thickness, v2 + (n2 + n1) * thickness, v2 + (n2 - n1) * thickness);
    p = q.writeByteArray(p);

    // end caps

    q = Quad(v1 + (n1 - n2) * thickness, v1 + (n1 + n2) * thickness, v1 + (n2 - n1) * thickness, v1 - (n1 + n2) * thickness);
    p = q.writeByteArray(p);

    q = Quad(v2 + (n1 - n2) * thickness, v2 + (n1 + n2) * thickness, v2 + (n2 - n1) * thickness, v2 - (n1 + n2) * thickness);
    p = q.flip().writeByteArray(p);

    return p;
}
