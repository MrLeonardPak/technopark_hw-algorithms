#include "set_graph.h"

#include <cassert>

namespace technopark::algorithms::graph {

SetGraph::SetGraph(size_t size) : graph_(size) {}

SetGraph::SetGraph(IGraph const& graph)
    : graph_(graph.VerticesCount(), std::set<size_t>()) {
  for (size_t i = 0; i < graph.VerticesCount(); i++) {
    for (auto& vertex : graph.GetNextVertices(i)) {
      graph_[i].insert(vertex);
    }
  }
}

void SetGraph::AddEdge(size_t from, size_t to) {
  assert(from < graph_.size());
  assert(to < graph_.size());

  graph_[from].insert(to);
}

size_t SetGraph::VerticesCount() const {
  return graph_.size();
}

std::vector<size_t> SetGraph::GetNextVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  return {graph_[vertex].begin(), graph_[vertex].end()};
}
std::vector<size_t> SetGraph::GetPrevVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<size_t>();
  for (size_t i = 0; i < graph_.size(); ++i) {
    if (graph_[i].find(vertex) != graph_[i].end()) {
      result.push_back(i);
    }
  }
  return result;
}

}  // namespace technopark::algorithms::graph