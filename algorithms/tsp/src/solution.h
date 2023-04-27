#ifndef LAB3_SOLUTION_H
#define LAB3_SOLUTION_H

#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <fstream>
#include <chrono>


// Структура, хранящая ребро графа
struct Edge {
    explicit Edge(int vertex = -1, int weight = INF) : vertex(vertex), weight(weight) {}

    int vertex;
    int weight;
};


// Структура, хранящая текущее состояние решения
struct State {
    explicit State(int cost = 0) : path_cost(cost) {}

    int path_cost;
    std::vector<int> hamiltonian_path;
};


// Класс, отвечающий за граф
class Graph {
public:
    // Конструктор
    explicit Graph(const std::string& fileName = "1.txt") : rank_matrix(0) { file.open(fileName); }
    // Деструктор
    ~Graph() { if(file.is_open()) { file.close(); } }

    // Считывает граф
    void readGraph();
    // Сортирует граф
    void sortGraph();

    // Возвращает ранг матрицы
    [[nodiscard]] int getRank() const { return rank_matrix; }

    // Выводит граф
    void printGraph() const;

    // Для удобства работы с классом перегружен оператор[]
    std::vector<Edge>& operator[](int vertex) { return graph[vertex]; }
private:
    // Метод, разделяющий строку
    std::vector<Edge> split(std::string row);

private:
    // Ранг матрицы
    int rank_matrix;
    // Файл, с которого считывается матрица
    std::fstream file;
    // Искомый граф
    std::map<int, std::vector<Edge>> graph;
};


// Класс, решающий задачу
class TSP {
public:
    // Конструктор
    explicit TSP(const std::string& fileName) : time(0), best_solution(INF), graph(fileName) {}

    // Рекурсивно находит решение задачи
    void tsp(State current_solution, int current_count, int current_vertex);

    // Вызывает все необходимые методы и инициализирует все нужные структуры для решения
    void solve();

    // Печатает ответ
    void printAnswer();
    // Выводит граф (нужно было для отладки программы, сейчас уже не используется нигде)
    [[maybe_unused]] void printGraph() const { graph.printGraph(); }
    // Выводит время
    void printTime() const { std::cout << "Время: " << time << '\n'; }

    // Возвращает лучшее решение
    [[nodiscard]] State getBestSolution() const { return best_solution; }
private:
    // Заполняет вектор, необходимый для оценки решения
    void setLowBound();
    // Высчитвает значение оценки для текущего решения
    int countLowBound(const State& current_solution);

private:
    // Хранит время
    double time;
    // Хранит граф
    Graph graph;
    // Текущее лучшее решение
    State best_solution;
    // Вектор посещенных вершин
    std::vector<bool> vertex_visited;
    // Вектор, хранящий необходимые элементы для нижней оценки
    std::vector<int> low_bound;
};

/**
 * Метод Graph::sortGraph сортирует ребра каждой вершины в графе в
 * порядке возрастания на основе их веса, используя std::sort и лямбда-функцию.
 **/
void Graph::sortGraph() {
    for (auto& element : graph) {
        std::sort(element.second.begin(), element.second.end(),
                  [](const Edge &first, const Edge &second) {
                      return first.weight < second.weight;
                  });
    }
}

/**
 * Метод Graph::readGraph считывает граф из файла и заполняет std::map графа вершинами и ребрами графа.
 * Каждая строка в файле соответствует вершине графа и содержит последовательность чисел,
 * представляющих веса ребер, которые инцидентны этой вершине.
 **/
void Graph::readGraph() {
    std::string row;
    while(std::getline(file, row)) {
        graph[rank_matrix++] = split(row);
    }
}

/**
 * Метод Graph::split принимает std::string в качестве
 * входных данных и разбивает строку по пробелу.
 * Затем каждое слово или число преобразуется преобразовывается к целочисленному типу,
 * а потом к Edge и добавляется в вектор, который возвращается методом.
 **/
std::vector<Edge> Graph::split(std::string row) {
    std::string delimiter = " ";

    std::vector<Edge> result;
    size_t position = 0;
    std::string substr;
    int vertex_counter = 0;

    auto castToInt = [](const std::string& str)
    { return str == "inf" || str == "-" ? INF : std::stoi(str); };
    auto implementEdge = [&](const std::string& str) {
        Edge edge;
        edge.weight = castToInt(str);
        edge.vertex = vertex_counter++;

        result.push_back(edge);
    };

    while ((position = row.find(delimiter)) != std::string::npos) {
        substr = row.substr(0, position);
        implementEdge(substr);
        row.erase(0, position + delimiter.length());
    }
    implementEdge(row);

    return result;
}

/**
 * Метод Graph::printGraph выводит вершины и ребра графа в стандартный поток вывода.
 * В скобках указывается сначала вершина, затем ее вес.
 **/
void Graph::printGraph() const {
    std::cout << "\n";
    for (const auto& edges : graph) {
        std::cout << edges.first + 1 << ": ";
        for (auto edge : edges.second) {
            std::cout << "(" << edge.vertex + 1 << ", " << edge.weight << ") ";
        }
        std::cout << "\n";
    }
}

/**
 * Метод TSP::printAnswer выводит ответ на задачу коммивояжера в стандартный поток вывода.
 * Если гамильтонов цикл найден, он выводит последовательность вершин в цикле и его общую стоимость.
 * Если гамильтонов цикл не найден, выводится сообщение об отсутствии цикла.
 **/
void TSP::printAnswer() {
    if (best_solution.hamiltonian_path.empty()) {
        std::cout << "Отсутствует гамильтонов цикл\n";
        return;
    }

    for (auto i : best_solution.hamiltonian_path) {
        std::cout << i + 1 << " ";
    }
    std::cout << "\nРасстояние: " << best_solution.path_cost << '\n';
}

/**
 * Метод TSP::solve считывает граф из файла, сортирует ребра каждой вершины,
 * вычисляет нижнюю границу решения и инициализирует текущее состояние решения.
 * Затем метод вызывает метод tsp для поиска всех возможных путей в графе, пока не будет найден гамильтонов цикл.
 * Метод также измеряет время, затраченное на решение задачи.
 **/
void TSP::solve() {
    auto start_time = std::chrono::steady_clock::now();
    graph.readGraph();
    graph.sortGraph();

    setLowBound();

    vertex_visited.resize(graph.getRank());
    vertex_visited.assign(vertex_visited.size(), false);

    State solution;
    solution.hamiltonian_path.push_back(0);

    tsp(solution, 1, 0);
    auto end_time = std::chrono::steady_clock::now();

    time = static_cast<std::chrono::duration<double>>(end_time - start_time).count();
}

/**
 * Метод TSP::tsp рекурсивно ищет все возможные пути в графе.
 * Метод вызывается методом решения с начальным состоянием current_solution,
 * содержащим ее стоимость и пройденный путь. Метод проходит все
 * исходящие ребра текущей вершины и рекурсивно вызывает себя с обновленным состоянием
 * для каждой соседней вершины, которая еще не была посещена. Метод выполняет откат,
 * когда все возможные пути от текущей вершины исследованы или когда нижняя граница
 * текущего решения больше или равна стоимости лучшего известного на данный момент решения.
 **/
void TSP::tsp(State current_solution, int current_count, int current_vertex) {
    if (countLowBound(current_solution) >= best_solution.path_cost) {
        return;
    }

    if (current_count == graph.getRank()) {
        const auto& last = graph[current_vertex];

        auto way_to_first = std::find_if(last.begin(), last.end(),
                                         [&](const Edge& edge) { return edge.vertex == 0; });

        if (way_to_first == last.end()) { return; }

        int total_cost = current_solution.path_cost + way_to_first->weight;
        current_solution.path_cost = total_cost;
        if (best_solution.path_cost > total_cost) {
            best_solution = current_solution;
            best_solution.hamiltonian_path.push_back(0);
        }
        return;
    }
    else {
        vertex_visited.at(current_vertex) = true;
        for (auto edge: graph[current_vertex]) {
            if (!vertex_visited.at(edge.vertex)) {
                vertex_visited.at(edge.vertex) = true;
                current_solution.path_cost += edge.weight;
                current_solution.hamiltonian_path.push_back(edge.vertex);

                tsp(current_solution, current_count + 1, edge.vertex);

                vertex_visited.at(edge.vertex) = false;
                current_solution.path_cost -= edge.weight;
                current_solution.hamiltonian_path.pop_back();
            }
        }
        vertex_visited.at(current_vertex) = false;
    }
}

/**
 * Метод TSP::setLowBound вычисляет нижнюю границу решения задачи коммивояжера,
 * суммируя веса наименьших ребер, инцидентных каждой вершине графа.
 **/
void TSP::setLowBound() {
    for (int i = 0; i < graph.getRank(); ++i) {
        low_bound.push_back(graph[i].at(0).weight);
    }
    std::sort(low_bound.begin(), low_bound.end());
}

/**
 * Метод TSP::countLowBound вычисляет нижнюю границу стоимости решения задачи
 * с учетом частичного решения current_solution.
 **/
int TSP::countLowBound(const State &current_solution) {
    int bound = current_solution.path_cost;
    for (size_t i = 0; i < graph.getRank() - current_solution.hamiltonian_path.size(); ++i) {
        bound += low_bound.at(i);
    }

    return bound;
}

#endif //LAB3_SOLUTION_H
