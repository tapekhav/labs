#include <iostream>
#include <vector>


// Класс, решающий задачу
class KMP {
public:
    // Конструктор
    explicit KMP(const std::string& original_string, const std::string& shift_string)
            : original_string(original_string), shift_string(shift_string),
            prefix_shift_string(shift_string.length()) {}

    // Вызывает нужные методы и печатает ответ на задачу
    void solveTask();
private:
    // Метод, проверяющий размеры строк
    [[nodiscard]] bool checkSizes() const { return original_string.length() == shift_string.length(); }
    // Метод, который ищет значения префикс-функции для
    void findPrefix();
    // Метод, реализующий циклический алгоритм КМП
    int cyclicKMP();

private:
    // Сдвинутая строка
    std::string shift_string;
    // Оригинальная строка
    std::string original_string;
    // Значения префикс-функции для строки shift_string
    std::vector<uint32_t> prefix_shift_string;
};

// Метод KMP::findPrefix вычисляет вектор префиксов для строки shift_string.
void KMP::findPrefix() {
    prefix_shift_string.at(0) = 0;

    for (size_t i = 1; i < shift_string.length(); ++i) {
        size_t previous_prefix_value = prefix_shift_string.at(i - 1);
        for (;shift_string.at(i) != shift_string.at(previous_prefix_value)
                && previous_prefix_value > 0;) {
            previous_prefix_value = prefix_shift_string.at(previous_prefix_value - 1);
        }

        previous_prefix_value += (shift_string.at(i) == shift_string.at(previous_prefix_value));
        prefix_shift_string.at(i) = previous_prefix_value;
    }
}

/**
 * KMP::cyclicKMP() - это метод класса KMP, который использует алгоритм Кнута-Морриса-Пратта
 * для проверки является ли shift_string циклическим сдвигом original_string.
 * Метод KMP::cyclicKMP() возвращает целое число - индекс начала строки shift_string
 * в строке original_string. Если строка shift_string не является циклическим сдвигом
 * строки original_string, метод возвращает -1.
 **/
int KMP::cyclicKMP() {
    size_t shift_index = 0;

    for (size_t i = 0; i < original_string.length(); ++i) {
        for (;shift_string.at(shift_index) != original_string.at(i) && shift_index > 0;) {
            shift_index = prefix_shift_string.at(shift_index - 1);
        }

        shift_index += (shift_string.at(shift_index) == original_string.at(i));

        if (shift_index == shift_string.length()) {
            return static_cast<int>(i - shift_string.length() + 1);
        }
    }

    return -1;
}


/**
 * Метод KMP::solveTask вызывает все необходимые для решения задачи методы, проверяет
 * размеры исходных строк и дублирует одну из строк.
 **/
void KMP::solveTask() {
    if (!checkSizes()) {
        std::cout << -1;
        return;
    }

    original_string += original_string;
    findPrefix();
    std::cout << cyclicKMP();
}


int main() {
    std::string original_string, shift_string;
    std::cin >> original_string >> shift_string;

    KMP solution(original_string, shift_string);
    solution.solveTask();

    return 0;
}

