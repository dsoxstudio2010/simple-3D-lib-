#include "../include/platform/x11_window.h"
#include "../include/core/vector.h"
#include "../include/core/matrix.h"
#include <math.h>
#include <unistd.h>

#define WIDTH 640
#define HEIGHT 480

// Определяем PI если не определен
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Вершины куба
Vec3 cube_vertices[] = {
    {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
    {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}
};

// Рёбра куба
int cube_edges[][2] = {
    {0,1}, {1,2}, {2,3}, {3,0},
    {4,5}, {5,6}, {6,7}, {7,4},
    {0,4}, {1,5}, {2,6}, {3,7}
};

int main() {
    X11Window* win = x11_window_create(WIDTH, HEIGHT, "3D Cube Demo");
    
    if (!win) {
        //printf("❌ Ошибка создания окна!\n");
        return 1;
    }
    
    float angle = 0.0f;
    float transform[4][4];
    float projection[4][4];
    float view[4][4];
    
    // Инициализация матриц
    mat4_identity(transform);
    mat4_identity(projection);
    mat4_identity(view);
    
    // Настраиваем проекцию
    mat4_perspective(projection, M_PI/3.0f, (float)WIDTH/HEIGHT, 0.1f, 100.0f);
    mat4_translate(view, 0, 0, -5); // Отодвигаем камеру
    
    while (x11_window_handle_events(win)) {
        x11_window_clear(win);
        
        // Обновляем преобразования
        angle += 0.01f;
        mat4_identity(transform);
        mat4_rotate_y(transform, angle);
        
        // Общая матрица преобразования
        float final[4][4];
        mat4_multiply(final, view, transform);
        mat4_multiply(final, projection, final);
        
        // Преобразуем и рисуем куб
        for (int i = 0; i < 12; i++) {
            Vec3 v1 = cube_vertices[cube_edges[i][0]];
            Vec3 v2 = cube_vertices[cube_edges[i][1]];
            
            // Применяем преобразования
            v1 = vec3_transform(v1, final);
            v2 = vec3_transform(v2, final);
            
            // Преобразуем в экранные координаты (от -1 до 1 -> 0 до WIDTH/HEIGHT)
            int x1 = (int)((v1.x + 1.0f) * 0.5f * WIDTH);
            int y1 = (int)((1.0f - (v1.y + 1.0f) * 0.5f) * HEIGHT);
            int x2 = (int)((v2.x + 1.0f) * 0.5f * WIDTH);
            int y2 = (int)((1.0f - (v2.y + 1.0f) * 0.5f) * HEIGHT);
            
            // Проверяем границы экрана
            if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT &&
                x2 >= 0 && x2 < WIDTH && y2 >= 0 && y2 < HEIGHT) {
                x11_window_draw_line(win, x1, y1, x2, y2, 0x00FF00);
            }
        }
        
        x11_window_update(win);
        usleep(16000); // ~60 FPS
    }
    
    x11_window_destroy(win);
    return 0;
}