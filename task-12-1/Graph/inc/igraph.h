#ifndef ALGORITHMS_IGRAPH_H
#define ALGORITHMS_IGRAPH_H

#include <functional>
#include <vector>

namespace technopark::algorithms::graph {

struct IGraph {
  virtual ~IGraph() = default;

  // Добавление ребра от from к to.
  virtual void AddEdge(size_t from, size_t to) = 0;

  virtual size_t VerticesCount() const = 0;

  virtual std::vector<size_t> GetNextVertices(size_t vertex) const = 0;
  virtual std::vector<size_t> GetPrevVertices(size_t vertex) const = 0;

  static void DFS(IGraph const& graph,
                  size_t start_vertex,
                  std::function<void(size_t)> callback);
  static void BFS(IGraph const& graph,
                  size_t start_vertex,
                  std::function<void(size_t)> callback);
};

}  // namespace technopark::algorithms::graph

#endif  // ALGORITHMS_IGRAPH_H