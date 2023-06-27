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

    inline vec3 operator+(vec3 a) const {
        return vec3(a.x + x, a.y + y, a.z + z);
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
};


struct vec2 {
    float x;
    float y;

    vec2() : x(0), y(0) {
    }

    vec2(float px, float py) : x(px), y(py) {
    }

    inline vec2 operator=(vec2 a) {
        x = a.x;
        y = a.y;
        return a;
    }

    inline vec2 operator+(vec2 a) {
        return vec2(a.x + x, a.y + y);
    }

    inline vec2 operator-(vec2 a) {
        return vec2(x - a.x, y - a.y);
    }

    inline vec2 operator*(float a) {
        return vec2(x * a, y * a);
    }
};
