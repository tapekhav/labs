#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

// Предварительно объявлен класс Node, чтобы использовать его в краткой записи с помощью using
class Node;

using Nodes = std::vector<Node>;
using graph_type = std::unordered_map<char, Nodes>;


// Структура, хранящая точку и стоимость пути до нее
struct Node {
    char point; // Точка
    float cost; // Стоимость пути до нее

    // Конструкторы
    explicit Node(char point = 'a', float cost = 0.0) : point(point), cost(cost) {}
    explicit Node(const std::pair<char, float>& node) : point(node.first), cost(node.second) {}

    /* Перегружен оператор равенства, который необходим для корректной работы
     * std::unordered_map c пользовательской структурой */
    bool operator==(const Node& other) const { return point == other.point && cost == other.cost; }
};

// Определен std::hash для Node, который нужен для корректной работы с std::unordered_map
template <>
struct std::hash<Node>
{
    std::size_t operator()(const Node& node) const
    {
        // Хэш-функция, преобразовывающая поля структуры
        return ((std::hash<char>()(node.point) ^ (std::hash<float>()(node.cost) << 1)) >> 1);
    }
};


/* Функция, считывающая граф.
 * Переменная from показывает из какой вершины идет путь.
 * Переменная to показывает в какую вершину направлен путь. */
graph_type read_graph() {
    graph_type graph;
    char from, to;
    float length;

    while (std::cin >> from >> to >> length) {
        graph[from].emplace_back(to, length);
    }

    return graph;
}


// Класс, реализующий решение жадного алгоритма
class Greedy {
public:
    // Конструктор
    Greedy(char start, char goal, graph_type graph)
            : goal(goal), graph(std::move(graph)) { answer.push_back(start); }

    // Сортирует считанный граф
    void sort_graph();
    // Жадный алгоритм, решающий задачу
    void greedy_algorithm(char current);
    // Печатает ответ
    void print_answer();
private:
    char goal; // конечная вершина
    graph_type graph; // структура, хранящая граф
    std::vector<char> answer; // вектор, хранящий ответ
};

// Сортирует рёбра графа по возрастанию их длины
void Greedy::sort_graph() {
    for(auto& i : graph) {
        std::sort(i.second.begin(), i.second.end(),
                  [](const Node& edge1, const Node& edge2) {
                      return edge1.cost < edge2.cost;
                  });
    }
}

/**
 * Рекурсивный алгоритм, решающий задачу.
 * По достижении конечной вершины алгоритм завершает работу.
 * Заранее все вершины графа были отсортиованы по возрастанию.
 * Если текущая вершина была найдена в графе, то просматриваются последовательно по возрастанию длины,
 * смежные вершины. Иначе ветка решений обрывается и последняя вершина удаляется из массива,
 * содержащего решение задачи.
 */
void Greedy::greedy_algorithm(char current) {
    if (current == goal) {
        return;
    }

    auto iter = graph.find(current);
    if (iter == graph.end()) {
        answer.pop_back();
        return;
    }

    for(const auto& elem : iter->second) {
        answer.push_back(elem.point);
        iter->second.pop_back();
        greedy_algorithm(elem.point);

        if (answer.back() == goal) {
            return;
        }
    }
    answer.pop_back();
}

// Печатает ответ на задачу
void Greedy::print_answer() {
    for (char i : answer) {
        std::cout << i;
    }
}


int main() {
    char start, final;
    std::cin >> start >> final;

    Greedy solver(start, final, read_graph());
    solver.sort_graph();
    solver.greedy_algorithm(start);

    solver.print_answer();


    return 0;
}



