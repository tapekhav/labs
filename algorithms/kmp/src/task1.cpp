#include <iostream>
#include <utility>
#include <vector>
#include <experimental/iterator>


// Класс, реализующий алгоритм KMP
class KMP {
public:
    // Конструктор
    explicit KMP(std::string pattern)
    : pattern(std::move(pattern)), prefix(pattern.length()) {}

    // Метод, который ищет значения префикс-функции
    void findPrefix();
    // Метод, реализующий алгоритм КМП
    void kmp(const std::string& text);

    // Возвращает лучшее решение
    [[nodiscard]] std::vector<uint32_t> getSolution() const { return pattern_matches; }

    // Печатает ответ на задачу
    void printAnswer() const;
private:
    // Значения префикс-функции
    std::vector<uint32_t> prefix;
    // Индексы найденных вхождения шаблона в тексте
    std::vector<uint32_t> pattern_matches;
    // Шаблон, который необходимо найти в заданном тексте
    const std::string pattern;
};

// Метод KMP::findPrefix вычисляет вектор префиксов для шаблонной строки pattern
void KMP::findPrefix() {
    prefix.at(0) = 0;

    for (size_t i = 1; i < pattern.length(); ++i) {
        uint32_t previous_prefix_value = prefix.at(i - 1);
        while (previous_prefix_value > 0 
                && pattern.at(i) != pattern.at(previous_prefix_value)) {
            previous_prefix_value = prefix.at(previous_prefix_value - 1);
        }

        previous_prefix_value += (pattern.at(i) == pattern.at(previous_prefix_value));
        prefix.at(i) = previous_prefix_value;
    }
}

/**
 * Метод KMP::kmp запускает алгоритм КМП на заданном тексте text для поиска
 * вхождений шаблонной строки. В этом методе используется вычисленный вектор
 * префиксов, чтобы быстро переходить к следующей позиции, если текущая не
 * соответствует шаблону.
 **/
void KMP::kmp(const std::string& text) {
    uint32_t pattern_index = 0;

    for (size_t i = 0; i < text.length(); ++i) {
        while (pattern_index > 0 && pattern.at(pattern_index) != text.at(i)) {
            pattern_index = prefix.at(pattern_index - 1);
        }

        pattern_index += (pattern.at(pattern_index) == text.at(i));

        if (pattern_index == pattern.length()) {
            pattern_matches.push_back(i - pattern.length() + 1);
            pattern_index = prefix.at(pattern_index - 1);
        }
    }
}

/**
 * Метод KMP::printAnswer печатает ответ на задачу. Если не было найдено
 * шаблона в тексте, то печатается -1 */
void KMP::printAnswer() const {
    if (pattern_matches.empty()) {
        std::cout << -1;
        return;
    }

    std::copy(pattern_matches.begin(), pattern_matches.end(),
              std::experimental::make_ostream_joiner(std::cout, ","));
}


int main() {
    std::string text, pattern;

    std::cin >> pattern >> text;

    KMP solve(pattern);
    solve.findPrefix();
    solve.kmp(text);

    solve.printAnswer();


    return 0;
}

