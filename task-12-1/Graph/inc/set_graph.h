#ifndef ALGORITHMS_SET_GRAPH_H
#define ALGORITHMS_SET_GRAPH_H

#include "igraph.h"

#include <set>

namespace technopark::algorithms::graph {

class SetGraph : public IGraph {
 public:
  SetGraph(size_t size);
  SetGraph(IGraph const& graph);
  ~SetGraph() = default;

  // Добавление ребра от from к to.
  void AddEdge(size_t from, size_t to) override;

  size_t VerticesCount() const override;

  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;

 private:
  std::vector<std::set<size_t>> graph_;
};

}  // namespace technopark::algorithms::graph

#endif  // ALGORITHMS_SET_GRAPH_H