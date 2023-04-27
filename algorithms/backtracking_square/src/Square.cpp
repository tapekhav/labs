#include "Square.h"

// Масштабирование
void Square::scale_square(int input_n, int decreased_n) {
    change_coordinate(coordinates.first, input_n, decreased_n);
    change_coordinate(coordinates.second, input_n, decreased_n);
    size = size * input_n / decreased_n;
}

// Масштабирование одной из координат
void Square::change_coordinate(int &coordinate, int input_n, int decreased_n) {
    coordinate = coordinate * input_n / decreased_n + 1;
}

// Перегрузка оператора <<
std::ostream& operator<<(std::ostream &os, const Square& sq) {
    return os << sq.coordinates.first << ' ' << sq.coordinates.second << ' ' << sq.size << '\n';
}
