#include "includes.h"

using namespace std;


vec3 frame[X_res][Y_res];

vec3 light_key_dir_norm = light_key_dir / sqrtf(light_key_dir.x*light_key_dir.x + light_key_dir.y*light_key_dir.y + light_key_dir.z*light_key_dir.z);
vec3 light_fill_dir_norm = light_fill_dir / sqrtf(light_fill_dir.x*light_fill_dir.x + light_fill_dir.y*light_fill_dir.y + light_fill_dir.z*light_fill_dir.z);
vec3 light_back_dir_norm = light_back_dir / sqrtf(light_back_dir.x*light_back_dir.x + light_back_dir.y*light_back_dir.y + light_back_dir.z*light_back_dir.z);


void print_pnm() {
    ofstream file;
    file.open(output_path);

    if(!file.is_open()) {
        cout << "Failed to open file " << output_path << endl;
        exit(3);
    }

    file << "P3" << endl;
    file << X_res << " " << Y_res << endl;
    file << "255" << endl;

    for(int y = Y_res-1; y >= 0; y--) {
        for(int x = 0; x < X_res; x++) {
            vec3 img_color = vec3(
                (int)clamp(frame[x][y].x * 255, 0.0f, 255.0f),
                (int)clamp(frame[x][y].y * 255, 0.0f, 255.0f),
                (int)clamp(frame[x][y].z * 255, 0.0f, 255.0f)
            );

            file << img_color.x << " ";
            file << img_color.y << " ";
            file << img_color.z << " ";
        }
        file << endl;
    }
}


void clear_frame() {
    for(int x = 0; x < X_res; x++)
        for(int y = 0; y < Y_res; y++)
            frame[x][y] = background_col;
}


float global_sdf(vec3 point) {
    float min_dist = object_list[0].sdf(point);

    for(int i = 1; i < object_list.size(); i++) {
        float dist = object_list[i].sdf(point);

        if(dist < min_dist)
            min_dist = dist;
    }

    return min_dist;
}


vec3 calc_normal(vec3 p) {
    vec3 normal = vec3(
        global_sdf(vec3(p.x + normal_estimation_epsilon, p.y, p.z)) - global_sdf(vec3(p.x - normal_estimation_epsilon, p.y, p.z)),
        global_sdf(vec3(p.x, p.y + normal_estimation_epsilon, p.z)) - global_sdf(vec3(p.x, p.y - normal_estimation_epsilon, p.z)),
        global_sdf(vec3(p.x, p.y, p.z  + normal_estimation_epsilon)) - global_sdf(vec3(p.x, p.y, p.z - normal_estimation_epsilon))
    );

    normal = normal / sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);

    return normal;
}


vec3 calc_lighting(vec3 normal) {
    vec3 col;

    // key
    float key = clamp(light_key_dir_norm.x*(-normal.x) + light_key_dir_norm.y*(-normal.y) + light_key_dir_norm.z*(-normal.z), 0.0f, 1.0f);
    col = col + (light_key_col * object_col * light_key_power) * key;

    // fill
    float fill = clamp(light_fill_dir_norm.x*(-normal.x) + light_fill_dir_norm.y*(-normal.y) + light_fill_dir_norm.z*(-normal.z), 0.0f, 1.0f);
    col = col + (light_fill_col * object_col * light_fill_power) * fill;

    // back
    float back = clamp(light_back_dir_norm.x*(-normal.x) + light_back_dir_norm.y*(-normal.y) + light_back_dir_norm.z*(-normal.z), 0.0f, 1.0f);
    col = col + (light_back_col * object_col * light_back_power) * back;

    return col;
}


vec3 cast_ray(vec3 dir) {
    vec3 ray_pos = cam_pos;
    float dist = global_sdf(ray_pos);

    for(int i = 0; i < max_ray_steps; i++) {

        if(dist < ray_collision_treshold) {
            return calc_lighting(calc_normal(ray_pos));
        }

        ray_pos = ray_pos + dir * dist;

        dist = global_sdf(ray_pos);
    }

    return background_col;
}


void raymarch() {
    float X_res_half = X_res / 2;
    float Y_res_half = Y_res / 2;
    float fov_half = fov / 2;

    float frame_size = 2 * tan(fov * 0.00872); // deg to rad and also divide by two
    float pixel_size = frame_size / X_res;

    for(int x = 0; x < X_res; x++){
        for(int y = 0; y < Y_res; y++) {
            float x_vec = ((float)x - X_res_half) * pixel_size;
            float y_vec = ((float)y - Y_res_half) * pixel_size;

            vec3 dir(x_vec, -1, y_vec);

            // cout << dir.z << endl;
            // cout << sqrtf(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z) << " ";
            dir = dir / sqrtf(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
            // cout << sqrtf(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z) << endl;

            // cout << dir.x << " " << dir.y << " " << dir.z << endl;

            // vec3 dir(0, -1, 0);

            frame[x][y] = cast_ray(dir);
        }
    }
}


void render() {
    clear_frame();
    raymarch();
    print_pnm();
}
