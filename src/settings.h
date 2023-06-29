#pragma once

// Global settings for the render


// Scene -----------------------------------------------------------------------

    // Camera
    const vec3 cam_pos = vec3(0, 5, 0);
    const vec3 cam_rot = vec3(0, 0, 0); // execution order: y(roll), x(pitch), z(pan)
    const float fov = 30;


    // Shader
    const float ambient_factor = 0.3;
    const float environment_factor = 0.4;
    const float diffuse_factor = 0.7;
    const float specular_factor = 0.35;

    const float roughness = 0.7; // 0 to 1


    // Objects
    const vec3 object_col = vec3(1.0, 0.85, 1.0);

    enum Sdf_Type {SPHERE, CUBE, CYLINDER}; // object types
    enum Bool_Type {UNION, DIFFERENCE, INTERSECT}; // ways to combine two objects

    const Sdf_Type obj1_type = SPHERE;
    const vec3 obj1_pos = vec3(0, 0, 0);
    const vec3 obj1_scale = vec3(1, 1, 1);
    const vec3 obj1_rot = vec3(0, 0, 0);

        const Bool_Type bool_type2 = DIFFERENCE; // How to combine obj1 and obj2
        const float smoothness2 = 0.02; // 0 to 1

    const Sdf_Type obj2_type = SPHERE;
    const vec3 obj2_pos = vec3(0.5, 0.5, -0.2);
    const vec3 obj2_scale = vec3(1, 1, 0.3);
    const vec3 obj2_rot = vec3(20, 0, 45);
    const bool obj2_enable = true;

        const Bool_Type bool_type3 = UNION; // How to combine obj1,2 and obj3
        const float smoothness3 = 0.15; // 0 to 1

    const Sdf_Type obj3_type = CYLINDER;
    const vec3 obj3_pos = vec3(0, 0, -2.4);
    const vec3 obj3_scale = vec3(0.4, 0.4, 4);
    const vec3 obj3_rot = vec3(0, 0, 0);
    const bool obj3_enable = true;


    // Lighing
    const vec3 environment_col = vec3(0.25, 0.1, 0.4);

    enum Light_Type {DIR, POINT}; // light types

    const Light_Type light_key_type = POINT;
    const vec3 light_key_dir = vec3(-1, -0.5, -0.4); // if DIR light; can never be zero
    const vec3 light_key_pos = vec3(2, 2, 1); // if POINT light
    const float light_key_power = 1;
    const vec3 light_key_col = vec3(1, 1, 0.9);
    const bool light_key_enable = true;

    const Light_Type light_fill_type = POINT;
    const vec3 light_fill_dir = vec3(0.5, -0.5, 0); // if DIR light; can never be zero
    const vec3 light_fill_pos = vec3(-2, 2, 0); // if POINT light
    const float light_fill_power = 0.3;
    const vec3 light_fill_col = vec3(0.9, 0.9, 1);
    const bool light_fill_enable = true;

    const Light_Type light_back_type = POINT;
    const vec3 light_back_dir = vec3(0.7, 0.7, -0.5); // if DIR light; can never be zero
    const vec3 light_back_pos = vec3(-2, -2, 2); // if POINT light
    const float light_back_power = 2;
    const vec3 light_back_col = vec3(0.4, 0.5, 1);
    const bool light_back_enable = true;



// Render ----------------------------------------------------------------------

    // General
    const int X_res = 1200;
    const int Y_res = 900;
    const std::string output_path = "output/image9.pnm";


    // Raymarching
    const float ray_collision_treshold = 0.001;
    const float max_ray_steps = 100;
    const float normal_estimation_epsilon = 0.001;
