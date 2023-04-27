#include <gtest/gtest.h>
#include "../solution.h"


// Пример из условия
TEST(Tests, ExampleTest){
    std::string full_path = PATH;
    full_path += "1.txt";

    TSP solution(full_path);
    solution.solve();

    std::vector<int> answer = {0, 1, 2, 3, 0};
    ASSERT_EQ(solution.getBest().way, answer);
    ASSERT_EQ(solution.getBest().cost, 4);
}

// Немного побольше тест
TEST(Tests, Test2){
    std::string full_path = PATH;
    full_path += "2.txt";

    TSP solution(full_path);
    solution.solve();

    std::vector<int> answer = {0, 1, 2, 3, 4, 5, 6, 0};
    ASSERT_EQ(solution.getBest().way, answer);
    ASSERT_EQ(solution.getBest().cost, 7);
}

// Матрица 15x15
TEST(Tests, Test3){
    std::string full_path = PATH;
    full_path += "3.txt";

    TSP solution(full_path);
    solution.solve();

    std::vector<int> answer = {0, 12, 6, 7, 5, 9, 13, 10, 8, 14, 11, 1, 4, 2, 3, 0};
    ASSERT_EQ(solution.getBest().way, answer);
    ASSERT_EQ(solution.getBest().cost, 1656);
}

// Матрица 20x20
TEST(Tests, Test4){
    std::string full_path = PATH;
    full_path += "4.txt";

    TSP solution(full_path);
    solution.solve();

    std::vector<int> answer = {0, 4, 13, 8, 11, 7, 5, 19, 15, 16, 2, 3, 10, 12, 18, 1, 6, 14, 17, 9, 0};
    ASSERT_EQ(solution.getBest().way, answer);
    ASSERT_EQ(solution.getBest().cost, 1541);
}

// Матрица 20x20, работает быстрее прошлого теста
TEST(Tests, Test5){
    std::string full_path = PATH;
    full_path += "5.txt";

    TSP solution(full_path);
    solution.solve();

    std::vector<int> answer = {0, 4, 14, 13, 10, 5, 1, 11, 9, 2, 6, 3, 15, 19, 12, 17, 18, 7, 16, 8, 0};
    ASSERT_EQ(solution.getBest().way, answer);
    ASSERT_EQ(solution.getBest().cost, 1187);
}

// Одинаковые значения в матрице, кроме одного
TEST(Tests, Test6){
    std::string full_path = PATH;
    full_path += "6.txt";

    TSP solution(full_path);
    solution.solve();

    std::vector<int> answer = {0, 1, 2, 4, 5, 3, 0};
    ASSERT_EQ(solution.getBest().way, answer);
    ASSERT_EQ(solution.getBest().cost, 11);
}

// Отсутствует гамильтонов цикл
TEST(Tests, Test7){
    std::string full_path = PATH;
    full_path += "7.txt";

    TSP solution(full_path);
    solution.solve();

    ASSERT_TRUE(solution.getBest().way.empty());
}

// Изолированная вершина
TEST(Tests, Test8){
    std::string full_path = PATH;
    full_path += "8.txt";

    TSP solution(full_path);
    solution.solve();

    ASSERT_TRUE(solution.getBest().way.empty());
}

// Все элементы матрицы одинаковые
TEST(Tests, Test9){
    std::string full_path = PATH;
    full_path += "9.txt";

    TSP solution(full_path);
    solution.solve();

    std::vector<int> answer = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    ASSERT_EQ(solution.getBest().way, answer);
    ASSERT_EQ(solution.getBest().cost, 10);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}