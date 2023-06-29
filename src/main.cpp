#include "includes.h"

using namespace std;


vector<Sdf_Object> object_list;
vector<Light> light_list;


void initial_condition() {
    object_list.emplace_back(obj1_type, UNION, 0, obj1_pos, obj1_scale, obj1_rot, false); // always visible
    object_list.emplace_back(obj2_type, bool_type2, smoothness2, obj2_pos, obj2_scale, obj2_rot, obj2_hide);
    object_list.emplace_back(obj3_type, bool_type3, smoothness3, obj3_pos, obj3_scale, obj3_rot, obj3_hide);

    light_list.emplace_back(DIR, vec3(0, 0, 0), light_key_dir, light_key_col, light_key_power, light_key_enable);
    light_list.emplace_back(DIR, vec3(0, 0, 0), light_fill_dir, light_fill_col, light_fill_power, light_fill_enable);
    light_list.emplace_back(DIR, vec3(0, 0, 0), light_back_dir, light_back_col, light_back_power, light_back_enable);
}


int main() {

    initial_condition();

    render();

    return(0);
}
