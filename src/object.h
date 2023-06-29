#pragma once

#include "util.h"

using namespace std;

// enum Sdf_Type {SPHERE, CUBE};


class Sdf_Object {
public:

    Sdf_Type type;
    Bool_Type bool_type;
    float bool_smooth;
    vec3 pos;
    vec3 scale;
    vec3 rot;
    bool enable;

    Sdf_Object(Sdf_Type ptype, Bool_Type pbool_type, float pbool_smooth, vec3 ppos, vec3 pscale, vec3 prot, bool penable)
        : type(ptype), bool_type(pbool_type), bool_smooth(pbool_smooth), pos(ppos), scale(pscale), rot(prot), enable(penable) {
    }

    vec3 transform(vec3 point) {
        // translate
        point = point - pos;

        //rotate
        vec3 rot_rad = rot * 0.01745329251; // deg to rad
        //  z-axis
        vec3 rot_tmp = point;
        point.x = rot_tmp.x * cos(rot_rad.z) - rot_tmp.y * sin(rot_rad.z);
        point.y = rot_tmp.x * sin(rot_rad.z) + rot_tmp.y * cos(rot_rad.z);
        //  x-axis
        rot_tmp = point;
        point.y = rot_tmp.y * cos(rot_rad.x) - rot_tmp.z * sin(rot_rad.x);
        point.z = rot_tmp.y * sin(rot_rad.x) + rot_tmp.z * cos(rot_rad.x);
        //  y-axis
        rot_tmp = point;
        point.x = rot_tmp.x * cos(rot_rad.y) - rot_tmp.z * sin(rot_rad.y);
        point.z = rot_tmp.x * sin(rot_rad.y) + rot_tmp.z * cos(rot_rad.y);

        // scale
        point = point / scale;

        return point;
    }

    float sdf(vec3 point) {
        float dist;
        point = transform(point);

        switch(type) {
            case SPHERE: dist = sphere_sdf(point); break;
            case CUBE: dist = cube_sdf(point); break;
            case CYLINDER: dist = cylinder_sdf(point); break;
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
        vec3 q = point.absolute() - 0.5f;
        vec3 r = vec3(max(q.x,0.0f), max(q.y,0.0f), max(q.z,0.0f));
        float l = sqrtf(r.x*r.x + r.y*r.y + r.z*r.z);
        return l + min(max(q.x,max(q.y,q.z)),0.0f);
    }

    float cylinder_sdf(vec3 point) {
        vec3 d(vec3(hypotf(point.x, point.y), point.z, 0).absolute() - vec3(0.5, 0.5, 0));
        return min(max(d.x,d.y),0.0f) + hypotf(max(d.x,0.0f),max(d.y,0.0f));
    }
};
