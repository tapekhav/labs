#ifndef SOLUTION_H
#define SOLUTION_H

#include "Matrix.h"
#include "Square.h"

// Класс, квадрирующий исходный квадрат
class Squaring {
public:
    // Конструктор
    // Всегда можно поставить 2 * n квадратов, поэтому инициализируем best_count = 2 * n + 1
    explicit Squaring(int size)
    : n(size), table(size), best_count(2 * n + 1), best_arr(best_count), cur_arr(best_count) {}

    // Метод, квадратирующий исходный квадрат(решение задачи)
    void squared_table();
    // Метод, печатающий ответ
    void print_answer();
private:
    // Метод, реализующий бэктрекинг
    void backtracking(int cur_count, int free_space);
    // Метод, уменьшающий исходный размер квадрата
    void decrease_size();
    // Метод, масштабирующий массив, в котором хранится лучшее решение
    void scale_array(int input_n);

    int n; // Размер изначального квадрата(исходный или уменьшенный)
    Matrix table; // Булевая матрица, позволяющая отслеживать занятую область исходного квадрата
    int best_count; // Минимальное количество квадратов, из которых можно построить исходный квадрат
    std::vector<Square> best_arr; // Массив лучшего решения(хранит координаты и размер обрезков)
    std::vector<Square> cur_arr; // Массив, который содержит текущее решение, выстроенное перебором
};


#endif
