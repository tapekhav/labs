cmake_minimum_required(VERSION 3.22.1)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest)
if (${GTest_FOUND})
    add_executable(test_solution
            solution.h
            tests/tests.cpp)

    target_link_libraries(test_solution
            ${CMAKE_THREAD_LIBS_INIT}
            GTest::GTest
            GTest::gtest_main
            GTest::gmock
            GTest::gmock_main
            )

    enable_testing()

endif (${GTest_FOUND})

# Некоторые константы, использующиеся в программе
add_compile_definitions(PATH="${CMAKE_CURRENT_SOURCE_DIR}/tests/files/")
add_compile_definitions(INF=INT16_MAX)
add_executable(lab3 solution.h main.cpp)
