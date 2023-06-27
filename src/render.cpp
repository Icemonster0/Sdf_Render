#include "includes.h"

using namespace std;


vec3 frame[X_res][Y_res];


void print_pnm() {
    ofstream file;
    file.open(output_path);

    file << "P3" << endl;
    file << X_res << " " << Y_res << endl;
    file << "255" << endl;

    for(int x = 0; x < X_res; x++) {
        for(int y = 0; y < Y_res; y++) {
            file << frame[x][y].x;
            file << frame[x][y].y;
            file << frame[x][y].z;
        }
    }
}


void clear_frame() {
    for(int x = 0; x < X_res; x++)
        for(int y = 0; y < Y_res; y++)
            frame[x][y] = background_col;
}


float global_sdf(vec3 point) {
    float min_dist = object_list[0]->sdf(point);

    for(int i = 1; i < object_list.size(); i++) {
        float dist = object_list[i]->sdf(point);

        if(dist < min_dist)
            min_dist = dist;
    }

    return min_dist;
}


vec3 cast_ray(vec3 dir) {
    vec3 ray_pos = cam_pos;
    float dist = global_sdf(ray_pos);

    for(int i = 0; i < max_ray_steps; i++) {
        if(dist < ray_collision_treshold)
            return object_col;

        ray_pos = ray_pos + dir * dist;

        dist = global_sdf(ray_pos);
    }

    return background_col;
}


void raymarch() {
    int X_res_half = X_res / 2;
    int Y_res_half = Y_res / 2;
    float fov_half = fov / 2;

    for(int x = 0; x < X_res; x++){
        for(int y = 0; y < Y_res; y++) {
            float x_deg = ((float)x / X_res_half + 1.0f) * fov_half;
            float y_deg = ((float)y / X_res_half + 1.0f) * fov_half;

            float vec_x = tan(x_deg * 0.0174);
            float vec_y = tan(y_deg * 0.0174);

            vec3 dir(vec_x, 1, vec_y);
            dir = dir / sqrtf(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);

            frame[x][y] = cast_ray(dir);
        }
    }
}


void render() {
    clear_frame();
    raymarch();
    print_pnm();
}
