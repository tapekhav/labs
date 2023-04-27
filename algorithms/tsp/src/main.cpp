#include "solution.h"

int main() {
    std::string full_path = PATH;
    full_path += "9.txt";

    TSP tsp(full_path);
    tsp.solve();

    tsp.printAnswer();
    tsp.printTime();

    return 0;
}
