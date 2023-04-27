#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template<class T>
using matrix = std::vector<std::vector<T>>;

// Класс булевой матрицы
// Нужен для отслеживания занятых областей в исходном квадрате
class Matrix {
public:
    // Конструктор
    explicit Matrix(int size = 0);

    // Геттер, возвращающий значение элемента матрицы, который находится в заданных координатах
    [[nodiscard]] bool get_cell(int x, int y) const;
    // Метод, проверяющий занята ли область матрицы другим квадратом
    [[nodiscard]] bool check_area(int x, int y, int size) const;

    // Метод, заполняющий/освобождающий область матрицы
    void fill_area(int x, int y, int size);
private:
    matrix<bool> table; // булевая матрица
};


#endif //MATRIX_H