#pragma once

#include "util.h"


// enum Light_Type {DIR, POINT};


class Light {
public:
    Light_Type type;
    vec3 pos;
    vec3 dir;
    vec3 color;
    float power;
    bool enable;

    Light(Light_Type ptype, vec3 ppos, vec3 pdir, vec3 pcolor, float ppower, bool penable)
        : type(ptype), pos(ppos), dir(pdir), color(pcolor), power(ppower), enable(penable) {
        dir = dir / sqrtf(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
    }

    vec3 calc_light(vec3 normal, vec3 point) {
        vec3 col;

        if(enable) {
            switch(type) {
                case DIR: col = calc_dir_light(normal); break;
                case POINT: col = calc_point_light(normal, point); break;
                default: std::cout << "Invalid Light Type" << std::endl; exit(4);
            }
        }

        return col;
    }

private:

    vec3 calc_dir_light(vec3 normal) {
        // Using Blinn-Phong method
        vec3 view(0, -1, 0);
        vec3 H_vec = (dir + view) / 2; // Blinn's simplification
        H_vec = H_vec / sqrtf(H_vec.x*H_vec.x + H_vec.y*H_vec.y + H_vec.z*H_vec.z);

        vec3 col;

        // diffuse
        col = col + object_col * color * power
            * std::max(-normal.x*dir.x - normal.y*dir.y - normal.z*dir.z, 0.0f)
            * (roughness * 0.5 + 0.5) // decrease diffuse amount with shininess
            * diffuse_factor;

        // specular
        col = col + color * power
            * powf(std::max(-normal.x*H_vec.x - normal.y*H_vec.y - normal.z*H_vec.z, 0.0f), std::pow(4000.0, 1.0 - roughness))
            * (std::pow(4.0, 1.0 - roughness) - 1.0) // increse specular amount with shininess
            * specular_factor;

        return col;
    }

    // TODO
    vec3 calc_point_light(vec3 normal, vec3 point) {
        return vec3();
    }
};
