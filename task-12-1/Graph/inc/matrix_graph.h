#ifndef ALGORITHMS_MATRIX_GRAPH_H
#define ALGORITHMS_MATRIX_GRAPH_H

#include "igraph.h"

namespace technopark::algorithms::graph {

class MatrixGraph : public IGraph {
 public:
  MatrixGraph(size_t size);
  MatrixGraph(IGraph const& graph);
  ~MatrixGraph() = default;

  // Добавление ребра от from к to.
  void AddEdge(size_t from, size_t to) override;

  size_t VerticesCount() const override;

  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;

 private:
  std::vector<std::vector<bool>> graph_;
};

}  // namespace technopark::algorithms::graph

#endif  // ALGORITHMS_MATRIX_GRAPH_H