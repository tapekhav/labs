#include <iostream>
#include "Squaring.h"

int main() {
    int n;
    std::cin >> n;

    Squaring solve(n);
    solve.squared_table();
    
    solve.print_answer();

    return 0;
}
