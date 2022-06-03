#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

struct IGraph {
  virtual ~IGraph() = default;

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

  virtual size_t VerticesCount() const = 0;

  virtual std::vector<int> GetNextVertices(int vertex) const = 0;
  virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
  ListGraph(int size);
  ListGraph(IGraph const& graph);
  ~ListGraph() = default;

  // Добавление ребра от from к to.
  void AddEdge(int from, int to) override;

  size_t VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<std::vector<int>> reverse_graph_;
};

ListGraph::ListGraph(int size) : graph_(size), reverse_graph_(size) {}

ListGraph::ListGraph(IGraph const& graph) {
  graph_.reserve(graph.VerticesCount());
  graph_.reserve(graph.VerticesCount());
  for (size_t i = 0; i < graph.VerticesCount(); ++i) {
    graph_[i] = graph.GetNextVertices(i);
    auto tmp_vert = graph.GetPrevVertices(i);
    for (size_t j = 0; j < tmp_vert.size(); ++j) {
      reverse_graph_[tmp_vert[j]].push_back(i);
    }
  }
}

void ListGraph::AddEdge(int from, int to) {
  assert(from < graph_.size());
  assert(to < graph_.size());

  graph_[from].push_back(to);
  graph_[to].push_back(from);
}

size_t ListGraph::VerticesCount() const {
  return graph_.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<int>(graph_[vertex].begin(), graph_[vertex].end());
  return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<int>(reverse_graph_[vertex].begin(),
                                 reverse_graph_[vertex].end());
  return result;
}

size_t BFS(IGraph const& graph, int start_vertex, int end_vertex) {
  auto vertex_queue = std::queue<int>();
  auto dist =
      std::vector<int>(graph.VerticesCount(), std::numeric_limits<int>::max());
  // auto parent = std::vector<int>(graph.VerticesCount());
  auto path_count = std::vector<size_t>(graph.VerticesCount());

  vertex_queue.push(start_vertex);
  dist[start_vertex] = 0;
  // parent[start_vertex] = -1;
  path_count[start_vertex] = 1;
  while (!vertex_queue.empty()) {
    int current = vertex_queue.front();
    vertex_queue.pop();
    std::vector<int> children = graph.GetNextVertices(current);
    for (auto&& child : children) {
      // Это условие работает при условии, что изначально dist заполнен max()
      if (dist[child] > dist[current] + 1) {
        vertex_queue.push(child);
        dist[child] = dist[current] + 1;
        // parent[child] = current;
        path_count[child] = path_count[current];
      } else if (dist[child] == dist[current] + 1) {
        path_count[child] += path_count[current];
      }
    }
  }
  return path_count[end_vertex];
}

void Run(std::istream& in, std::ostream& out) {
  size_t v, n;
  in >> v >> n;

  auto graph = ListGraph(v);
  for (size_t i = 0; i < n; ++i) {
    int a, b;
    in >> a >> b;
    graph.AddEdge(a, b);
  }
  int u, w;
  in >> u >> w;
  out << BFS(graph, u, w) << std::endl;
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "4 5 0 1 0 2 1 2 1 3 2 3 0 3"
       << "\n";
    Run(in, out);
    std::cout << out.str();
    assert(out.str() == "2\n");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  // Run(std::cin, std::cout);
  TestContest();
  return 0;
}
