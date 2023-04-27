#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

// Класс, описывающий параметры квадрата и взаимодействия с ними
class Square {
public:
    // Конструктор
    explicit Square(int x = 0, int y = 0, int size = 0)
            : coordinates(x, y), size(size) {}

    // Метод, масштабирующий координаты и размер квадрата
    void scale_square(int input_n, int decreased_n);
    // Объявление дружественности для функции, перегружающей оператор вывода
    friend std::ostream& operator<<(std::ostream &os, const Square& sq);
private:
    // Метод, масштабирующий координату
    void change_coordinate(int& coordinate, int input_n, int decreased_n);

    std::pair<int, int> coordinates; // Координаты левого верхнего угла квадрата(x;y)
    int size; // Размер стороны квадрата
};


#endif // SQUARE_H
