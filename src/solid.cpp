#include "solid.h"

float *draw_tube(float *p, float thickness, Vec3<float> v1, Vec3<float> v2, Vec3<float> n1, Vec3<float> n2)
{
    // -n1
    p = (v1 - (n1 + n2) * thickness).write(p);
    p = (v1 - (n1 - n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);

    p = (v2 - (n1 - n2) * thickness).write(p);
    p = (v2 - (n1 + n2) * thickness).write(p);
    p = (v1 - (n1 + n2) * thickness).write(p);

    // +n1
    p = (v1 + (n1 + n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);
    p = (v2 + (n1 - n2) * thickness).write(p);

    p = (v2 + (n1 - n2) * thickness).write(p);
    p = (v2 + (n1 + n2) * thickness).write(p);
    p = (v1 + (n1 + n2) * thickness).write(p);

    // +n2
    p = (v1 - (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);

    p = (v2 + (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 + n2) * thickness).write(p);

    // // -n2
    p = (v1 + (n1 - n2) * thickness).write(p);
    p = (v1 - (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 + n2) * thickness).write(p);

    p = (v2 - (n1 + n2) * thickness).write(p);
    p = (v2 + (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);

    // v1 cap
    p = (v1 - (n1 + n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);
    p = (v1 - (n1 - n2) * thickness).write(p);

    p = (v1 + (n1 + n2) * thickness).write(p);
    p = (v1 - (n1 - n2) * thickness).write(p);
    p = (v1 + (n1 - n2) * thickness).write(p);

    // v2 cap
    p = (v2 + (n1 - n2) * thickness).write(p);
    p = (v2 - (n1 + n2) * thickness).write(p);
    p = (v2 - (n1 - n2) * thickness).write(p);

    p = (v2 - (n1 - n2) * thickness).write(p);
    p = (v2 + (n1 + n2) * thickness).write(p);
    p = (v2 + (n1 - n2) * thickness).write(p);

    return p;
}
