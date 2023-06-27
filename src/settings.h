#pragma once

// Global settings for the render


// Scene -----------------------------------------------------------------------
    // Camera
    const vec3 cam_pos = vec3(0, 2, 0);
    const float fov = 70;

    // Lighing
    const vec3 light_key_dir = vec3(-1, -0.5, -0.4);
    const float light_key_power = 1;
    const vec3 light_key_col = vec3(1, 1, 0.8);

    const vec3 light_fill_dir = vec3(0.5, -0.5, 0);
    const float light_fill_power = 0.4;
    const vec3 light_fill_col = vec3(0.9, 0.9, 1);

    const vec3 light_back_dir = vec3(0.7, 0.7, -0.5);
    const float light_back_power = 3;
    const vec3 light_back_col = vec3(0.3, 0.4, 1);


// Render ----------------------------------------------------------------------
    // General
    const int X_res = 1200;
    const int Y_res = 900;
    const std::string output_path = "output/image3.pnm";

    // Raymarching
    const float ray_collision_treshold = 0.01;
    const float max_ray_steps = 100;
    const float normal_estimation_epsilon = 0.01;

    // Colors
    const vec3 background_col = vec3(0.25, 0.25, 0.25);
    const vec3 object_col = vec3(0.9, 0.2, 0.1);
