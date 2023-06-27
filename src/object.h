#pragma once

#include "util.h"


enum Sdf_Type {SPHERE, CUBE};


class Sdf_Object {
public:

    Sdf_Type type;
    vec3 pos;
    vec3 scale;

    Sdf_Object(Sdf_Type ptype, vec3 ppos, vec3 pscale) : type(ptype), pos(ppos), scale(pscale) {
    }

    float sdf(vec3 point) {
        float dist;
        switch(type) {
            case SPHERE: dist = sphere_sdf(point); break;
            case CUBE: dist = cube_sdf(point); break;
            default: std::cout << "Invalid Sdf Type" << std::endl; exit(2);
        }
        return dist;
    }

private:

    float sphere_sdf(vec3 point) {
        vec3 diff = vec3(point.x - pos.x, point.y - pos.y, point.z - pos.z);

        return sqrtf(diff.x*diff.x + diff.y*diff.y + diff.z*diff.z) - 0.5;
    }

    // TODO
    float cube_sdf(vec3 point) {
        return 0;
    }
};
