#pragma once

// Global settings for the render


// Scene -----------------------------------------------------------------------
    // Camera
    const vec3 cam_pos = vec3(0, 1, 0);
    const float fov = 90;


// Render ----------------------------------------------------------------------
    // General
    const int X_res = 100;
    const int Y_res = 100;
    const std::string output_path = "output/image1.pnm";

    // Raymarching
    const float ray_collision_treshold = 0.01;
    const float max_ray_steps = 100;

    // Colors
    const vec3 background_col = vec3(0.25, 0.25, 0.25);
    const vec3 object_col = vec3(0.9, 0.2, 0.1);
