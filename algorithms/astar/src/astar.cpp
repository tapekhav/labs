#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <numeric>


// Код дублирован, так как степик не позволяет загрузить несколько файлов
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

// Класс, реализующий алгоритм А*
class AStar {
public:
    // Конструктор
    explicit AStar(char start, char goal, graph_type graph = {})
            : goal(goal), start(start), graph(std::move(graph)) {}

    // Метод, реализующий алгоритм А*
    bool A_star();
    // Печатает ответ
    void print_answer();
private:
    // Эвристическая функция, оценивающая расстояние от вершины x до конечной вершины
    [[nodiscard]] inline float heuristic(char current) const;
    // Находит минимальное значение эвристической функции "расстояние + стоимость" для вершины x
    char min_heuristic_plus_cost(const std::vector<char>& array);

    std::unordered_map<char, float> heuristic_plus_cost; // хранит значения функции "расстояние + стоимость" для всех x
    char start, goal; // начальная и конечные вершины
    graph_type graph; // структура, хранящая граф
    std::unordered_map<char, char> parents; // хранит родителей вершин, которые включены в итоговое решение
};


/** Этот метод реализует алгоритм A* для поиска кратчайшего пути до заданной вершины.
  * Алгоритм A* находит кратчайший путь до нужно вершины, используя эвристическую функцию,
  * которая оценивает оставшееся расстояние от каждой вершины до конечной вершины.
  * Алгоритм поддерживает два списка вершин: список обработанных вершин
  * и список вершин, которые нужно обработать. Алгоритм выбирает следующую вершину
  * для обработки из списка вершин, которые еще необходимо обработать,
  * на основе суммы стоимости достижения этой вершины из начальной вершины
  * и предполагаемого оставшегося расстояния до конечной вершины,
  * которое было оценено с помощью эвристической функции. Алгоритм продолжается
  * до тех пор, пока не будет достигнута конечная вершина или не останется вершин,
  * которые нужно обработать.
  * @return буллевое значение, которая показывает была ли найдена нужная вершина
  */
bool AStar::A_star() {
    std::vector<char> used, need_to_check;
    need_to_check.push_back(start);

    std::unordered_map<char, float> cost_to_final;
    cost_to_final[start] = 0;
    heuristic_plus_cost[start] = cost_to_final[start] + heuristic(start);

    while (!need_to_check.empty()) {
        char current = min_heuristic_plus_cost(need_to_check);
        if (current == goal) {
            return true;
        }

        need_to_check.erase(std::remove(need_to_check.begin(), need_to_check.end(), current),
                            need_to_check.end());
        used.push_back(current);

        for (auto v : graph[current]) {
            float tentative_score = cost_to_final[current] + v.cost;
            if ((std::find(used.begin(), used.end(), v.point) == used.end() && *used.end() != v.point)
                || tentative_score < cost_to_final[v.point])  {
                used.push_back(v.point);
                parents[v.point] = current;
                cost_to_final[v.point] = tentative_score;
                heuristic_plus_cost[v.point] = cost_to_final[v.point] + heuristic(v.point);
                if (std::find(need_to_check.begin(), need_to_check.end(), v.point) == need_to_check.end()
                    && *need_to_check.end() != v.point) {
                    need_to_check.push_back(v.point);
                }
            }
        }
    }
    return false;
}

// Выводит значения из структуры, хранящей родителей вершин, которые включены в итоговое решение.
void AStar::print_answer() {
    std::vector<char> result;
    char current = goal;

    while (parents[current] != current) {
        result.insert(result.begin(), current);
        current = parents[current];
    }

    for (auto element : result) {
        std::cout << element;
    }
}

// Эвристическая функция
float AStar::heuristic(char current) const {
    return static_cast<float>(goal - current);
}

// Нахождение минимальной вершины по оценке стоимость + эвристика
char AStar::min_heuristic_plus_cost(const std::vector<char> &array) {
    float min = std::numeric_limits<float>::infinity();
    char result;

    for (auto element : array) {
        min = std::min(min, heuristic_plus_cost[element]);
        result = heuristic_plus_cost[element] == min ? element : result;
    }

    return result;
}


int main() {
    char start, final;

    std::cin >> start >> final;

    AStar a_star(start, final, read_graph());

    a_star.A_star();
    a_star.print_answer();


    return 0;
}

