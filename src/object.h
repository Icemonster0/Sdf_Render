#pragma once

#include "util.h"


class Sdf_Object {
public:
    vec3 pos;
    vec3 scale;

    Sdf_Object(vec3 ppos, vec3 pscale) : pos(ppos), scale(pscale) {
    }

    virtual ~Sdf_Object();

    virtual float sdf(vec3 point);

    vec3 get_pos() {
        return pos;
    }
};


class Sdf_Sphere : public Sdf_Object {
public:

    Sdf_Sphere(vec3 ppos, vec3 pscale) : Sdf_Object(ppos, pscale) {
    }

    float sdf(vec3 point) {
        vec3 diff = vec3(point.x - Sdf_Object::pos.x, point.y - Sdf_Object::pos.y, point.z - Sdf_Object::pos.z);

        return sqrtf(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z);
    }
};
