#pragma once

#include "vec3.h"

using namespace std;
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
                case DIR: col = calc_dir_light(normal, point); break;
                case POINT: col = calc_point_light(normal, point); break;
                default: cout << "Invalid Light Type" << endl; exit(4);
            }
        }

        return col;
    }

private:

    vec3 blinn_phong(vec3 point, vec3 light, vec3 normal) {
        // Using Blinn-Phong method
        vec3 view = point - cam_pos;
        view = view / sqrtf(view.x*view.x + view.y*view.y + view.z*view.z);

        vec3 H_vec = (dir + view) / 2; // Blinn's simplification
        H_vec = H_vec / sqrtf(H_vec.x*H_vec.x + H_vec.y*H_vec.y + H_vec.z*H_vec.z);

        vec3 col;

        // diffuse
        col = col + object_col * color * power
            * max(-normal.x*light.x - normal.y*light.y - normal.z*light.z, 0.0f)
            * (roughness * 0.7 + 0.3) // decrease diffuse amount with shininess
            * diffuse_factor;

        // specular
        col = col + color * power
            * powf(max(-normal.x*H_vec.x - normal.y*H_vec.y - normal.z*H_vec.z, 0.0f), pow(4000.0, 1.0 - roughness))
            * (pow(4.0, 1.0 - roughness) - 1.0) // increse specular amount with shininess
            * specular_factor;


        if(shadows) {
            col = col * cast_shadow_ray(light * -1, point);
        }

        return col;
    }

    float cast_shadow_ray(vec3 dir, vec3 point) {
        vec3 ray_pos = point;
        float dist;
        float min_dist;

        // So that the soft shadow doesnt detect the surface the shadow is to be cast on:
        ray_pos = ray_pos + dir * max(shadow_softness, ray_collision_treshold);

        for(int i = 0; i < max_shadow_ray_steps; i++) {
            // cout << dist << endl;
            dist = global_sdf(ray_pos);
            if(type == POINT) {
                // cout << "?";
                float light_dist = (ray_pos-pos).length();
                // cout << light_dist << endl;
                dist = min(dist, light_dist);
                if(light_dist < shadow_softness) {
                    // cout << "X";
                    return clamp(min_dist / shadow_softness, 0.0f, 1.0f);
                }
            }

            if(dist < shadow_softness && dist < min_dist) {
                min_dist = dist;
            }
            if(dist < ray_collision_treshold) {
                // cout << "X";
                return 0;
            }

            ray_pos = ray_pos + dir * dist;
        }
        cout << " ";
        return clamp(min_dist / shadow_softness, 0.0f, 1.0f);
    }

    vec3 calc_dir_light(vec3 normal, vec3 point) {
        vec3 col = blinn_phong(point, dir, normal);

        return col;
    }

    vec3 calc_point_light(vec3 normal, vec3 point) {
        vec3 light_dir = point - pos;
        float light_length = sqrtf(light_dir.x*light_dir.x + light_dir.y*light_dir.y + light_dir.z*light_dir.z);

        light_dir = light_dir / light_length;

        vec3 col = blinn_phong(point, light_dir, normal);

        col = col / (light_length*light_length) * 5.0;

        return col;
    }
};
