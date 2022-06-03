#include "matrix_graph.h"

#include <cassert>

namespace technopark::algorithms::graph {

MatrixGraph::MatrixGraph(size_t size)
    : graph_(size, std::vector<bool>(size, false)) {}

MatrixGraph::MatrixGraph(IGraph const& graph)
    : graph_(graph.VerticesCount(),
             std::vector<bool>(graph.VerticesCount(), false)) {
  for (size_t i = 0; i < graph.VerticesCount(); ++i) {
    for (auto& vertex : graph.GetNextVertices(i))
      graph_[i][vertex] = true;
  }
}

void MatrixGraph::AddEdge(size_t from, size_t to) {
  assert(from < graph_.size());
  assert(to < graph_.size());

  graph_[from][to] = true;
}

size_t MatrixGraph::VerticesCount() const {
  return graph_.size();
}

std::vector<size_t> MatrixGraph::GetNextVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<size_t>();
  for (size_t i = 0; i < graph_.size(); ++i) {
    if (graph_[vertex][i])
      result.push_back(i);
  }
  return result;
}

std::vector<size_t> MatrixGraph::GetPrevVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<size_t>();
  for (size_t i = 0; i < graph_.size(); ++i) {
    if (graph_[i][vertex])
      result.push_back(i);
  }
  return result;
}

}  // namespace technopark::algorithms::graph
