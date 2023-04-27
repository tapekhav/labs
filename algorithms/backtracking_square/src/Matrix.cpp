#include "Matrix.h"

// Инициализация пустой матрицы(все значения равны false).
Matrix::Matrix(int size) {
    for (size_t i = 0; i < size; ++i) {
        table.emplace_back(size, false);
    }
}

// Возвращает значение элемента матрицы.
bool Matrix::get_cell(int x, int y) const {
    return table.at(y).at(x);
}

// Проверка области на наличие других квадратов на ней.
bool Matrix::check_area(int x, int y, int size) const {
    for (int i = y; i < y + size; ++i) {
        for (int j = x; j < x + size; ++j) {
            if (table.at(i).at(j)) {
                return false;
            }
        }
    }

    return true;
}

// Изменяются все значения в некоторой области на противоположные.
void Matrix::fill_area(int x, int y, int size) {
    for (int i = y; i < y + size; ++i) {
        for (int j = x; j < x + size; ++j) {
            table.at(i).at(j).flip();
        }
    }
}
