#include "includes.h"

using namespace std;


vector<Sdf_Object> object_list;
vector<Light> light_list;


void initial_condition() {
    object_list.emplace_back(obj1_type, obj1_pos, obj1_scale, obj1_rot);
    object_list.emplace_back(obj2_type, obj2_pos, obj2_scale, obj2_rot);

    light_list.emplace_back(DIR, vec3(0, 0, 0), light_key_dir, light_key_col, light_key_power);
    light_list.emplace_back(DIR, vec3(0, 0, 0), light_fill_dir, light_fill_col, light_fill_power);
    light_list.emplace_back(DIR, vec3(0, 0, 0), light_back_dir, light_back_col, light_back_power);
}


int main() {

    initial_condition();

    render();

    return(0);
}
