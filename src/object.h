#pragma once

#include "util.h"

using namespace std;

// enum Sdf_Type {SPHERE, CUBE};


class Sdf_Object {
public:

    Sdf_Type type;
    vec3 pos;
    vec3 scale;
    vec3 rot;

    Sdf_Object(Sdf_Type ptype, vec3 ppos, vec3 pscale, vec3 prot) : type(ptype), pos(ppos), scale(pscale), rot(prot) {
    }

    vec3 transform(vec3 point) {
        //rotate
        //  x-axis
        vec3 rot_tmp = point;
        point.y = rot_tmp.y * cos(rot.x) - rot_tmp.z * sin(rot.x);
        point.z = rot_tmp.y * sin(rot.x) + rot_tmp.z * cos(rot.x);
        //  y-axis
        rot_tmp = point;
        point.x = rot_tmp.x * cos(rot.y) - rot_tmp.z * sin(rot.y);
        point.z = rot_tmp.x * sin(rot.y) + rot_tmp.z * cos(rot.y);
        //  z-axis
        rot_tmp = point;
        point.x = rot_tmp.x * cos(rot.z) - rot_tmp.y * sin(rot.z);
        point.y = rot_tmp.x * sin(rot.z) + rot_tmp.y * cos(rot.z);

        // scale
        point = point / scale;

        // translate
        point = point - pos;

        return point;
    }

    float sdf(vec3 point) {
        float dist;
        point = transform(point);

        switch(type) {
            case SPHERE: dist = sphere_sdf(point); break;
            case CUBE: dist = cube_sdf(point); break;
            default: std::cout << "Invalid Sdf Type" << std::endl; exit(2);
        }

        dist = dist * min(scale.x, min(scale.y, scale.z)); // compensating for scale
        return dist;
    }

private:

    float sphere_sdf(vec3 point) {
        return sqrtf(point.x*point.x + point.y*point.y + point.z*point.z) - 0.5;
    }

    float cube_sdf(vec3 point) {
        vec3 q = vec3(abs(point.x), abs(point.y), abs(point.z)) - scale / 2;
        vec3 r = vec3(max(q.x,0.0f), max(q.y,0.0f), max(q.z,0.0f));
        float l = sqrtf(r.x*r.x + r.y*r.y + r.z*r.z);
        return l + min(max(q.x,max(q.y,q.z)),0.0f);
    }
};
