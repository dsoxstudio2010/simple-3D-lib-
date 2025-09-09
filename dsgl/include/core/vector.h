#ifndef VECTOR_H
#define VECTOR_H
// fack you
typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y, z, w;
} Vec4;

// baze
Vec3 vec3_create(float x, float y, float z);
Vec3 vec3_add(Vec3 a, Vec3 b); // ebana mazofaka
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_mul(Vec3 v, float scalar);
Vec3 vec3_div(Vec3 v, float scalar);

// vectors
float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
float vec3_length(Vec3 v);
Vec3 vec3_normalize(Vec3 v);

// huina
Vec3 vec3_transform(Vec3 v, float matrix[4][4]);

#endif


// UWU
//syka im ebal ety huinu