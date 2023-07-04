#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <unistd.h>

// util
#include "vec3.h"
#include "timer.h"

// settings
#include "settings.h"

// variables
extern vec3 cam_pos;
extern vec3 cam_rot;
extern float fov;

// functions
void render();
float global_sdf(vec3 point);

// classes
#include "object.h"
#include "light.h"

// objects
extern std::vector<Sdf_Object> object_list;
extern std::vector<Light> light_list;
