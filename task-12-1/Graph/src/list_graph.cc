#include "list_graph.h"

#include <cassert>

namespace technopark::algorithms::graph {

ListGraph::ListGraph(std::size_t size) : graph_(size), reverse_graph_(size) {}

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

void ListGraph::AddEdge(size_t from, size_t to) {
  assert(from < graph_.size());
  assert(to < graph_.size());

  graph_[from].push_back(to);
  reverse_graph_[to].push_back(from);
}

size_t ListGraph::VerticesCount() const {
  return graph_.size();
}

std::vector<size_t> ListGraph::GetNextVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  auto result =
      std::vector<size_t>(graph_[vertex].begin(), graph_[vertex].end());
  return result;
}

std::vector<size_t> ListGraph::GetPrevVertices(size_t vertex) const {
  assert(vertex < graph_.size());

  auto result = std::vector<size_t>(reverse_graph_[vertex].begin(),
                                    reverse_graph_[vertex].end());
  return result;
}

}  // namespace technopark::algorithms::graph