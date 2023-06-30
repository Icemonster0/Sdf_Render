#include "includes.h"

using namespace std;


vector<Sdf_Object> object_list;
vector<Light> light_list;

vec3 cam_pos = camera_pos;
vec3 cam_rot = camera_rot;
float fov = camera_fov;


vector<vector<float>> get_params(ifstream &file) {
    vector<vector<float>> params;

    for(int i = 0; true; i++) {
        params.push_back(vector<float>());

        while(true) {
            while(file.peek() == ' ') {
                file.get();
            }

            if(file.peek() == '\n') {
                file.get();
                return params;
            }

            if(file.peek() == '|') {
                file.get();
                break;
            }

            float value;
            file >> value;
            params[i].push_back(value);
        }
    }

    return params;
}


Bool_Type interpret_bool_type(int t) {
    switch(t) {
        case 1: return UNION;
        case 2: return DIFFERENCE;
        case 3: return INTERSECT;
        default: cout << scene_path << " : Bad bool mode" << endl; exit(7);
    }
}


void load_scene() {
    cout << "Loading scene " << scene_path << "..." << endl << endl;

    ifstream file(scene_path);
    if(!file.is_open()) {
        cout << "Failed to open file " << scene_path << ". Does it exist?" << endl;
        exit(6);
    }

    while(!file.eof() && file.peek() != -1) {
        start_again:

        while(file.peek() == ' ' || file.peek() == '\n' || file.peek() == '\t')
            file.get();

        if(file.peek() == '#') {
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            goto start_again;
        }

        char key;
        key = file.get();

        file.ignore(1, ':');

        vector<vector<float>> p = get_params(file);

        switch(key) {
            case 'C': cam_pos.x = p[0][0];
                      cam_pos.y = p[0][1];
                      cam_pos.z = p[0][2];
                      cam_rot.x = p[1][0];
                      cam_rot.y = p[1][1];
                      cam_rot.z = p[1][2];
                      fov = p[2][0];
                      cout << " Loaded Camera" << endl;
                      break;
            case 's': object_list.emplace_back(SPHERE, interpret_bool_type(p[3][0]), p[4][0], // bool, smooth
                      vec3(p[0][0], p[0][1], p[0][2]), // pos
                      vec3(p[1][0], p[1][1], p[1][2]), // scale
                      vec3(p[2][0], p[2][1], p[2][2]), // rot
                      true);
                      cout << " Loaded Sphere" << endl;
                      break;
            case 'c': object_list.emplace_back(CUBE, interpret_bool_type(p[3][0]), p[4][0], // bool, smooth
                      vec3(p[0][0], p[0][1], p[0][2]), // pos
                      vec3(p[1][0], p[1][1], p[1][2]), // scale
                      vec3(p[2][0], p[2][1], p[2][2]), // rot
                      true);
                      cout << " Loaded Cube" << endl;
                      break;
            case 'y': object_list.emplace_back(CYLINDER, interpret_bool_type(p[3][0]), p[4][0], // bool, smooth
                      vec3(p[0][0], p[0][1], p[0][2]), // pos
                      vec3(p[1][0], p[1][1], p[1][2]), // scale
                      vec3(p[2][0], p[2][1], p[2][2]), // rot
                      true);
                      cout << " Loaded Cylinder" << endl;
                      break;
            case 'f': object_list.emplace_back(FLOOR, interpret_bool_type(p[3][0]), p[4][0], // bool, smooth
                      vec3(p[0][0], p[0][1], p[0][2]), // pos
                      vec3(p[1][0], p[1][1], p[1][2]), // scale
                      vec3(p[2][0], p[2][1], p[2][2]), // rot
                      true);
                      cout << " Loaded Floor" << endl;
                      break;
            case 'd': light_list.emplace_back(DIR, vec3(), // pos
                      vec3(p[0][0], p[0][1], p[0][2]), // dir
                      vec3(p[1][0], p[1][1], p[1][2]), // col
                      p[2][0], true); // pow
                      cout << " Loaded Directional Light" << endl;
                      break;
            case 'p': light_list.emplace_back(DIR, vec3(p[0][0], p[0][1], p[0][2]), // pos
                      vec3(1, 1, 1), // dir
                      vec3(p[1][0], p[1][1], p[1][2]), // col
                      p[2][0], true); // pow
                      cout << " Loaded Point Light" << endl;
                      break;
            default: cout << scene_path << ": Bad key" << endl; exit(7);
        }
    }

    cout << endl;

    file.close();
}


void initial_condition() {
    if(import_scene) {
        load_scene();
    }
    else {
        object_list.emplace_back(obj1_type, UNION, 0, obj1_pos, obj1_scale, obj1_rot, true); // always visible
        object_list.emplace_back(obj2_type, bool_type2, smoothness2, obj2_pos, obj2_scale, obj2_rot, obj2_enable);
        object_list.emplace_back(obj3_type, bool_type3, smoothness3, obj3_pos, obj3_scale, obj3_rot, obj3_enable);

        light_list.emplace_back(light_key_type, light_key_pos, light_key_dir, light_key_col, light_key_power, light_key_enable);
        light_list.emplace_back(light_fill_type, light_fill_pos, light_fill_dir, light_fill_col, light_fill_power, light_fill_enable);
        light_list.emplace_back(light_back_type, light_back_pos, light_back_dir, light_back_col, light_back_power, light_back_enable);
    }
}


int main() {
    cout << endl;

    initial_condition();

    render();

    cout << "Done!" << endl << endl;
    return(0);
}
