#pragma once


struct vec3 {
    float x;
    float y;
    float z;

    vec3() : x(0), y(0), z(0) {
    }

    vec3(float px, float py, float pz) : x(px), y(py), z(pz) {
    }

    inline vec3 operator=(vec3 a) {
        x = a.x;
        y = a.y;
        z = a.z;
        return a;
    }

    inline vec3 operator+(float a) const {
        return vec3(x + a, y + a, z + a);
    }

    inline vec3 operator+(vec3 a) const {
        return vec3(a.x + x, a.y + y, a.z + z);
    }

    inline vec3 operator-(float a) const {
        return vec3(x - a, y - a, z - a);
    }

    inline vec3 operator-(vec3 a) const {
        return vec3(x - a.x, y - a.y, z - a.z);
    }

    inline vec3 operator*(float a) const {
        return vec3(x * a, y * a, z * a);
    }

    inline vec3 operator*(vec3 a) const {
        return vec3(x * a.x, y * a.y, z * a.z);
    }

    inline vec3 operator/(float a) const {
        return vec3(x / a, y / a, z / a);
    }

    inline vec3 operator/(vec3 a) const {
        return vec3(x / a.x, y / a.y, z / a.z);
    }

    inline vec3 absolute() {
        return vec3(std::abs(x), std::abs(y), std::abs(z));
    }

    vec3 rotate(vec3 rot) {
        vec3 rot_rad = rot * 0.01745329251; // deg to rad
        vec3 vec = vec3(x, y, z);
        //  y-axis
        vec3 rot_tmp = vec;
        vec.x = rot_tmp.x * cos(rot_rad.y) - rot_tmp.z * sin(rot_rad.y);
        vec.z = rot_tmp.x * sin(rot_rad.y) + rot_tmp.z * cos(rot_rad.y);
        //  x-axis
        rot_tmp = vec;
        vec.y = rot_tmp.y * cos(rot_rad.x) - rot_tmp.z * sin(rot_rad.x);
        vec.z = rot_tmp.y * sin(rot_rad.x) + rot_tmp.z * cos(rot_rad.x);
        //  z-axis
        rot_tmp = vec;
        vec.x = rot_tmp.x * cos(rot_rad.z) - rot_tmp.y * sin(rot_rad.z);
        vec.y = rot_tmp.x * sin(rot_rad.z) + rot_tmp.y * cos(rot_rad.z);

        return vec;
    }

    inline vec3 blend(vec3 vec, float fac) {
        return vec3(std::lerp(x, vec.x, fac), std::lerp(y, vec.y, fac), std::lerp(z, vec.z, fac));
    }

    inline float length() {
        return sqrtf(x*x + y*y + z*z);
    }
};
