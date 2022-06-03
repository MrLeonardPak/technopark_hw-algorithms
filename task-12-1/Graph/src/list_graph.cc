#include "list_graph.h"

namespace technopark::algorithms::graph {

ListGraph::ListGraph(std::size_t size) {
  graph_.resize(size);
  reverse_graph_.resize(size);
}

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
  graph_[from].push_back(to);
  reverse_graph_[to].push_back(from);
}

int ListGraph::VerticesCount() const {
  return graph_.size();
}

std::vector<size_t> ListGraph::GetNextVertices(size_t vertex) const {
  auto result =
      std::vector<size_t>(graph_[vertex].begin(), graph_[vertex].end());
  return result;
}

std::vector<size_t> ListGraph::GetPrevVertices(size_t vertex) const {
  auto result = std::vector<size_t>(reverse_graph_[vertex].begin(),
                                    reverse_graph_[vertex].end());
  return result;
}

}  // namespace technopark::algorithms::graph