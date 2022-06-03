#ifndef ALGORITHMS_ARC_GRAPH_H
#define ALGORITHMS_ARC_GRAPH_H

#include "igraph.h"

namespace technopark::algorithms::graph {

class ArcGraph : public IGraph {
 public:
  ArcGraph(size_t size);
  ArcGraph(IGraph const& graph);
  ~ArcGraph() = default;

  // Добавление ребра от from к to.
  void AddEdge(size_t from, size_t to) override;

  size_t VerticesCount() const override;

  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;

 private:
  size_t count_ = 0;
  std::vector<std::pair<size_t, size_t>> graph_;
};

}  // namespace technopark::algorithms::graph

#endif  // ALGORITHMS_ARC_GRAPH_H