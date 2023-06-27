#include "includes.h"

using namespace std;


vector<Sdf_Object> object_list;


void initial_condition() {
    object_list.emplace_back(SPHERE, vec3(0, 0, 0), vec3(1, 1, 1));
}


int main() {

    initial_condition();

    render();

    return(0);
}
