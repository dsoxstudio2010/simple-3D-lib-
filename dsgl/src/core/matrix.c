#include "core/matrix.h"
#include <math.h>

void mat4_identity(float matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void mat4_multiply(float result[4][4], float a[4][4], float b[4][4]) {
    float temp[4][4];
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                temp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    // copy res
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = temp[i][j];
        }
    }
}

void mat4_translate(float matrix[4][4], float x, float y, float z) {
    float translation[4][4] = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };
    
    float temp[4][4];
    mat4_multiply(temp, matrix, translation);
    
    // copy back
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}

void mat4_rotate_y(float matrix[4][4], float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    
    float rotation[4][4] = {
        {c, 0, s, 0},
        {0, 1, 0, 0},
        {-s, 0, c, 0},
        {0, 0, 0, 1}
    };
    
    float temp[4][4];
    mat4_multiply(temp, matrix, rotation);
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}

void mat4_perspective(float matrix[4][4], float fov, float aspect, float near, float far) {
    float f = 1.0f / tanf(fov / 2.0f);
    float range = near - far;
    
    float perspective[4][4] = {
        {f / aspect, 0, 0, 0},
        {0, f, 0, 0},
        {0, 0, (far + near) / range, 2 * far * near / range},
        {0, 0, -1, 0}
    };
    
    mat4_multiply(matrix, matrix, perspective);
}