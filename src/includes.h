#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

// util
#include "util.h"

// settings
#include "settings.h"

// classes
#include "object.h"
#include "light.h"

// objects
extern std::vector<Sdf_Object> object_list;
extern std::vector<Light> light_list;

// functions
void render();
