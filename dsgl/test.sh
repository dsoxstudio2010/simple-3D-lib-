#!/bin/bash

echo "🔨 Сборка без rasterizer..."

cd ..

# Компилируем все необходимые файлы
gcc -I./include \
    src/core/vector.c \
    src/core/matrix.c \
    src/platform/x11_window.c \
    src/demo_cube.c \
    -lX11 -lm -o cube_demo

if [ $? -eq 0 ]; then
    echo "✅ Сборка завершена!"
    echo "🎯 Запуск: ./cube_demo"
else
    echo "❌ Ошибка сборки!"
    echo "Проверьте наличие файлов:"
    ls -la include/core/
    ls -la src/core/
fi
