#include "Squaring.h"


// Печатает ответ.
void Squaring::print_answer() {
    std::cout << best_count << '\n';
    for (size_t i = 0; i < best_count; ++i) {
        std::cout << best_arr.at(i);
    } 
}

void Squaring::squared_table() {
    int input_n = n;
    // Квадраты со стороной n, где n - составное число,
    // квадрируются так же, как и квадраты,
    // у которых размер их стороны равен наименьшему делителю стороны исходного квадрата.
    // Поэтому для оптимазации можно попробовать уменьшить размер исходного квадрата.
    decrease_size();
    // Изначально в матрице размера nxn, отслеживающей занятые области исходного квадрата,
    // свободны все элементы(n * n элементов).
    int free_space = n * n;

    // Можно увидеть, что в квадрат размера n, где n - простое число,
    // всегда можно добавить первым и самым большим квадрат размера (n + 1) / 2
    // И рядом с ним добавить квадраты размером на единицу меньше
    cur_arr.at(0) = Square(0, 0, (n + 1) / 2);
    cur_arr.at(1) = Square(0, (n + 1) / 2, n - (n + 1) / 2);
    cur_arr.at(2) = Square((n + 1) / 2, 0, n - (n + 1) / 2);

    // Для того, чтобы отслеживать заполняемость исходного квадрата,
    // помечаются области соответствующие добавленным квадратам в матрице,
    // которая отслеживает занятые области исходного квадрата.
    table.fill_area(0, 0, (n + 1) / 2);
    table.fill_area(0, (n + 1) / 2, n - (n + 1) / 2);
    table.fill_area((n + 1) / 2, 0, n - (n + 1) / 2);

    // Вычитается площадь занятой области
    free_space -= ((n + 1) / 2) * ((n + 1) / 2);
    free_space -= 2 * (n - ((n + 1) / 2)) * (n - ((n + 1) / 2));

    // Полный перебор всех возможных вариантов квадрирования с учетом оптимизаций.
    backtracking(3, free_space);
    // Масштабирование параметров уменьшенного исходного квадрата.
    scale_array(input_n);
}

void Squaring::backtracking(int cur_count, int free_space) {
    // Если результат хуже или равен лучшему результату,
    // то нет смысла продолжать дальше перебор.
    if (best_count <= cur_count) {
        return;
    }

    // Подобрано новое лучшее решение.
    if (free_space == 0) {
        best_count = cur_count;
        best_arr = cur_arr;
        return;
    }

    // Если текущее решение до начала перебора только на единицу меньше лучшего,
    // то оно минимум будет такое же, как и лучшее.
    if (cur_count == best_count - 1) {
        return;
    }

    // Начало перебора
    for(int x = 0; x < n; ++x) {
        for(int y = 0; y < n; ++y) {
            if (!table.get_cell(x, y)) {
                // Подбор максимального размера квадрата с учетом всех ограничений.
                int max_side = std::min(n - 1, std::min(n - x, n - y));
                for(int side = max_side; side > 0; --side) {
                    // Если площадь этого квадрата не превышает количество свободных клеток,
                    // то можно попробовать его поставить.
                    if (side * side <= free_space) {
                        // Если по текущим координатам область в матрице свободна,
                        // то можно поставить квадрат
                        if (table.check_area(x, y, side)) {
                            table.fill_area(x, y, side);
                            cur_arr.at(cur_count) = Square(x, y, side);
                            backtracking(cur_count + 1, free_space - side * side);
                            table.fill_area(x, y, side);
                        }
                    }
                }
                // Если не было поставлено ни одного квадрата в текущих координатах,
                // то можно не рассматривать дальше решения этой ветки
                if (!table.get_cell(x, y))
                    return;
            }
        }
    }
}

// Масштабируются все элементы массивы лучшего решения.
void Squaring::scale_array(int input_n) {
    for (size_t i = 0; i < best_count; ++i) {
        best_arr.at(i).scale_square(input_n, n);
    }
}

// Рассматриваются только 2, 3, 5 в качестве делителей,
// так как все составные числа <= 40 содержат хотя бы один из них.
void Squaring::decrease_size() {
    if (n % 2 == 0) {
        n = 2;
    }
    else if (n % 3 == 0) {
        n = 3;
    }
    else if (n % 5 == 0) {
        n = 5;
    }
}
