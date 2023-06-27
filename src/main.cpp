#include "includes.h"

using namespace std;


vector<Sdf_Object*> object_list;


void initial_condition() {
    // borked af
    // Sdf_Sphere sphere(vec3(0, 0, 0), vec3(1, 1, 1));
    // object_list.push_back(&sphere);
}


int main() {

    initial_condition();

    render();

    return(0);
}
