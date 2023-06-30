#include "includes.h"

using namespace std;


vec3 frame[X_res][Y_res];


void print_pnm() {
    cout << "Saving image..." << endl;

    ofstream file;
    file.open(output_path);

    if(!file.is_open()) {
        cout << "Failed to open file " << output_path << ". Does the path exist?" << endl;
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
    for(int x = 0; x < X_res; x++) {
        for(int y = 0; y < Y_res; y++) {
            frame[x][y] = environment_col;
        }
    }
}


float smooth_min(float a, float b, float k) {
    // float h = max(k - abs(a - b), 0.0f) / k;
    // return min(a, b) - h*h*h*k*1/6.0;
    float h = clamp(0.5 + 0.5*(a-b)/k, 0.0, 1.0);
    float l = a + (b - a) * h;
    return l - k*h*(1.0-h);
}


float bool_union(float asdf, float bsdf, float k) {
    if(k != 0)
        return smooth_min(asdf, bsdf, k);
    else
        return min(asdf, bsdf);
}


float bool_difference(float asdf, float bsdf, float k) {
    if(k != 0)
        return smooth_min(asdf, -bsdf, -k);
    else
        return max(asdf, -bsdf);
}


float bool_intersect(float asdf, float bsdf, float k) {
    if(k != 0)
        return smooth_min(asdf, bsdf, -k);
    else
        return max(asdf, bsdf);
}


float global_sdf(vec3 point) {
    float dist;

    dist = object_list[0].sdf(point);

    for(int i = 1; i < object_list.size(); i++) {
        if(object_list[i].enable) {
            switch(object_list[i].bool_type) {
                case UNION: dist = bool_union(dist, object_list[i].sdf(point), object_list[i].bool_smooth); break;
                case DIFFERENCE: dist = bool_difference(dist, object_list[i].sdf(point), object_list[i].bool_smooth); break;
                case INTERSECT: dist = bool_intersect(dist, object_list[i].sdf(point), object_list[i].bool_smooth); break;
                default: std::cout << "Bool Type " << i+1 << " Invalid" << std::endl; exit(5);
            }
        }
    }

    return dist;
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


vec3 calc_lighting(vec3 normal, vec3 point) {
    vec3 col;

    for(auto &light : light_list) {
        col = col + light.calc_light(normal, point);
    }

    // ambient lighting
    col = col + object_col * ambient_factor;

    // environment lighting
    vec3 view = vec3(0, -1, 0).rotate(cam_rot);
    float fresnel = 1.0 - std::clamp(-normal.x*view.x - normal.y*view.y - normal.z*view.z, 0.0f, 1.0f);
    col = col + environment_col * fresnel * environment_factor;

    return col;
}


vec3 cast_ray(vec3 dir) {
    vec3 ray_pos = cam_pos;
    float dist;
    float ray_length = 0;

    for(int i = 0; i < max_ray_steps; i++) {

        dist = global_sdf(ray_pos);
        ray_length += dist;

        if(dist < 0) {
            return vec3(0, 0, 0);
        }
        else if(dist < ray_collision_treshold) {
            vec3 col = calc_lighting(calc_normal(ray_pos), ray_pos);
            if(fog)
                col = col.blend(environment_col, clamp(ray_length / fog_dist, 0.0f, 1.0f));
            return col;
        }

        ray_pos = ray_pos + dir * dist;
    }

    return environment_col;
}


void raymarch() {
    float X_res_half = X_res / 2;
    float Y_res_half = Y_res / 2;
    float fov_half = fov / 2;

    float frame_size = 2 * tan(fov * 0.00872664625); // deg to rad and also divide by two
    float pixel_size = frame_size / X_res;

    #pragma omp parallel for schedule(static) collapse(2)
    for(int x = 0; x < X_res; x++){
        for(int y = 0; y < Y_res; y++) {
            float x_vec = ((float)x - X_res_half) * pixel_size;
            float y_vec = ((float)y - Y_res_half) * pixel_size;

            vec3 dir(x_vec, -1, y_vec);

            dir = dir / sqrtf(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);

            dir = dir.rotate(cam_rot);

            frame[x][y] = cast_ray(dir);
        }
    }
}


void render() {
    cout << "Rendering..." << endl;

    clear_frame();
    raymarch();
    print_pnm();
}
