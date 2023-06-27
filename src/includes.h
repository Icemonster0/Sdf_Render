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

// objects
extern std::vector<Sdf_Object*> object_list;

// functions
void render();
