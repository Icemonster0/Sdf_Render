#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

// util
#include "vec3.h"

// settings
#include "settings.h"

// functions
void render();
float global_sdf(vec3 point);

// classes
#include "object.h"
#include "light.h"

// objects
extern std::vector<Sdf_Object> object_list;
extern std::vector<Light> light_list;
