#include "core/vector.h"
#include <math.h>

Vec3 vec3_create(float x, float y, float z) {
    Vec3 v = {x, y, z};
    return v;
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 vec3_mul(Vec3 v, float scalar) {
    return (Vec3){v.x * scalar, v.y * scalar, v.z * scalar};
}

Vec3 vec3_div(Vec3 v, float scalar) {
    return (Vec3){v.x / scalar, v.y / scalar, v.z / scalar};
}

float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

float vec3_length(Vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3_normalize(Vec3 v) {
    float length = vec3_length(v);
    if (length > 0) {
        return vec3_div(v, length);
    }
    return v;
}

Vec3 vec3_transform(Vec3 v, float matrix[4][4]) {
    Vec3 result;
    result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3];
    result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3];
    result.z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3];
    float w = matrix[3][0] * v.x + matrix[3][1] * v.y + matrix[3][2] * v.z + matrix[3][3];
    
    if (w != 0.0f) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }
    
    return result;
}