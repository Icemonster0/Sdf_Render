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

    vec3 absolute() {
        return vec3(std::abs(x), std::abs(y), std::abs(z));
    }
};
