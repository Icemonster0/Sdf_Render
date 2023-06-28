#pragma once

// Global settings for the render


// Scene -----------------------------------------------------------------------
    // Camera
    const vec3 cam_pos = vec3(0, 5, 0);
    const float fov = 30;

    // Shader
    const float ambient_factor = 0.2;
    const float environment_factor = 0.4;
    const float diffuse_factor = 0.7;
    const float specular_factor = 0.35;

    const float roughness = 0.7; // 0 to 1

    // Objects
    const vec3 object_col = vec3(0.9, 0.2, 0.1);

    enum Sdf_Type {SPHERE, CUBE}; // object types

    const Sdf_Type obj1_type = CUBE;
    const vec3 obj1_pos = vec3(0, 0, 0);
    const vec3 obj1_scale = vec3(0.9, 0.9, 0.9);
    const vec3 obj1_rot = vec3(-0.3, 0.1, 0.5);

    enum Bool_Type {UNION, DIFFERENCE, INTERSECT}; // ways to combine obj1 and obj2
    const Bool_Type bool_type = INTERSECT;
    const bool smooth = true;
    const float smoothness = 0.01; // 0 to 1

    const Sdf_Type obj2_type = SPHERE;
    const vec3 obj2_pos = vec3(0, 0, 0);
    const vec3 obj2_scale = vec3(1.1, 1.1, 1.1);
    const vec3 obj2_rot = vec3(0, 0, 0);

    // Lighing
    const vec3 environment_col = vec3(0.75, 0.5, 0.35);

    const bool enable_lights = true;

    enum Light_Type {DIR, POINT}; // light types

    const Light_Type light_key_type = DIR;
    const vec3 light_key_dir = vec3(-1, -0.5, -0.4);
    const float light_key_power = 1;
    const vec3 light_key_col = vec3(1, 1, 0.8);

    const Light_Type light_fill_type = DIR;
    const vec3 light_fill_dir = vec3(0.5, -0.5, 0);
    const float light_fill_power = 0.3;
    const vec3 light_fill_col = vec3(0.9, 0.9, 1);

    const Light_Type light_back_type = DIR;
    const vec3 light_back_dir = vec3(0.7, 0.7, -0.5);
    const float light_back_power = 2;
    const vec3 light_back_col = vec3(0.3, 0.4, 1);


// Render ----------------------------------------------------------------------
    // General
    const int X_res = 1200;
    const int Y_res = 900;
    const std::string output_path = "output/image7.pnm";

    // Raymarching
    const float ray_collision_treshold = 0.001;
    const float max_ray_steps = 100;
    const float normal_estimation_epsilon = 0.001;
