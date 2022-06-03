/**
 * @file 14-3.cc
 * @author Leonard Pak
 * @brief Требуется отыскать самый выгодный маршрут между городами. Требования:
 * время работы O((N+M)logN), где N-количество городов, M-известных дорог между
 * ними. Формат входных данных. Первая строка содержит число N – количество
 * городов. Вторая строка содержит число M - количество дорог. Каждая следующая
 * строка содержит описание дороги (откуда, куда, время в пути). Последняя
 * строка содержит маршрут (откуда и куда нужно доехать). Формат выходных
 * данных. Вывести длину самого выгодного маршрута.
 * @version 0.1
 * @date 2022-06-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

class ListGraph {
 public:
  ListGraph(int size);
  ~ListGraph() = default;

  // Добавление ребра от from к to.
  void AddEdge(int from, int to, int weight);

  size_t VerticesCount() const;

  std::vector<std::pair<int, int>> GetNextVertices(int vertex) const;

 private:
  std::vector<std::vector<std::pair<int, int>>> graph_;
};

ListGraph::ListGraph(int size) : graph_(size) {}

void ListGraph::AddEdge(int from, int to, int weight) {
  graph_[from].push_back(std::make_pair(weight, to));
  graph_[to].push_back(std::make_pair(weight, from));
}

size_t ListGraph::VerticesCount() const {
  return graph_.size();
}

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
  return graph_[vertex];
}

size_t Dijkstra(ListGraph const& graph,
                size_t start_vertex,
                size_t end_vertex) {
  auto dist = std::vector<size_t>(graph.VerticesCount(),
                                  std::numeric_limits<size_t>::max());
  dist[start_vertex] = 0;
  auto vertex_queue = std::queue<std::pair<int, int>>();
  vertex_queue.push(std::make_pair(0, start_vertex));
  while (!vertex_queue.empty()) {
    std::pair<int, int> current = vertex_queue.front();
    vertex_queue.pop();
    if (dist[current.second] < current.first) {
      continue;
    }
    for (std::pair<int, int> next : graph.GetNextVertices(current.second)) {
      if (dist[next.second] == std::numeric_limits<size_t>::max()) {
        dist[next.second] = dist[current.second] + next.first;
        vertex_queue.push(std::make_pair(next.first, next.second));
      } else if (dist[current.second] + next.first < dist[next.second]) {
        dist[next.second] = dist[current.second] + next.first;
        vertex_queue.push(std::make_pair(dist[next.second], next.second));
      }
    }
  }
  return dist[end_vertex];
}

void Run(std::istream& in, std::ostream& out) {
  size_t n, m;
  in >> n >> m;
  auto graph = ListGraph(n);
  for (size_t i = 0; i < m; ++i) {
    size_t from, to, weight;
    in >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }
  size_t start, end;
  in >> start >> end;
  out << Dijkstra(graph, start, end) << std::endl;
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "6 "
          "9 "
          "0 3 1 "
          "0 4 2 "
          "1 2 7 "
          "1 3 2 "
          "1 4 3 "
          "1 5 3 "
          "2 5 3 "
          "3 4 4 "
          "3 5 6 "
          "0 2"
       << std::endl;
    Run(in, out);
    assert(out.str() == "9\n");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  Run(std::cin, std::cout);
  // TestContest();
  return 0;
}