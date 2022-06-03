#include "arc_graph.h"

#include <cassert>

namespace technopark::algorithms::graph {

ArcGraph::ArcGraph(size_t size) : count_(size) {}

ArcGraph::ArcGraph(IGraph const& graph) : count_(graph.VerticesCount()) {
  for (size_t i = 0; i < count_; ++i) {
    for (auto const& vertex : graph.GetNextVertices(i)) {
      graph_.emplace_back(i, vertex);
    }
  }
}

void ArcGraph::AddEdge(size_t from, size_t to) {
  assert(from < graph_.size());
  assert(to < graph_.size());

  graph_.emplace_back(from, to);
}

size_t ArcGraph::VerticesCount() const {
  return count_;
}

std::vector<size_t> ArcGraph::GetNextVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<size_t>();
  for (auto const& pair : graph_) {
    if (pair.first == vertex) {
      result.push_back(pair.second);
    }
  }
  return result;
}

std::vector<size_t> ArcGraph::GetPrevVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<size_t>();
  for (auto const& pair : graph_) {
    if (pair.second == vertex) {
      result.push_back(pair.first);
    }
  }
  return result;
}

}  // namespace technopark::algorithms::graph