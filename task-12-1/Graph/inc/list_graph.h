#ifndef ALGORITHMS_LIST_GRAPH_H
#define ALGORITHMS_LIST_GRAPH_H

#include "igraph.h"

namespace technopark::algorithms::graph {

class ListGraph : public IGraph {
 public:
  ListGraph(size_t size);
  ListGraph(IGraph const& graph);
  ~ListGraph() = default;

  // Добавление ребра от from к to.
  void AddEdge(size_t from, size_t to) override;

  int VerticesCount() const override;

  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;

 private:
  std::vector<std::vector<size_t>> graph_;
  std::vector<std::vector<size_t>> reverse_graph_;
};

}  // namespace technopark::algorithms::graph

#endif  // ALGORITHMS_LIST_GRAPH_H