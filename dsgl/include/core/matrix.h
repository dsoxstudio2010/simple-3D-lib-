#ifndef MATRIX_H
#define MATRIX_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void mat4_identity(float matrix[4][4]);
void mat4_multiply(float result[4][4], float a[4][4], float b[4][4]);
void mat4_translate(float matrix[4][4], float x, float y, float z);
void mat4_rotate_x(float matrix[4][4], float angle);
void mat4_rotate_y(float matrix[4][4], float angle);
void mat4_rotate_z(float matrix[4][4], float angle);
void mat4_scale(float matrix[4][4], float x, float y, float z);
void mat4_perspective(float matrix[4][4], float fov, float aspect, float near, float far);

#endif