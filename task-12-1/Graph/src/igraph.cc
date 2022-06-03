#include "igraph.h"

#include <algorithm>
#include <queue>
#include <stack>

namespace technopark::algorithms::graph {

void IGraph::DFS(IGraph const& graph,
                 size_t start_vertex,
                 std::function<void(size_t)> callback) {
  auto visited = std::vector<bool>(graph.VerticesCount(), false);
  auto vertex_stack = std::stack<size_t>();

  vertex_stack.push(start_vertex);
  visited[start_vertex] = true;
  while (!vertex_stack.empty()) {
    size_t current = vertex_stack.top();
    vertex_stack.pop();
    callback(current);
    std::vector<size_t> children = graph.GetNextVertices(current);
    for (size_t i = children.size(); i > 0; --i) {
      if (!visited[children[i - 1]]) {
        vertex_stack.push(children[i - 1]);
        visited[children[i - 1]] = true;
      }
    }
  }
}

void IGraph::BFS(IGraph const& graph,
                 size_t start_vertex,
                 std::function<void(size_t)> callback) {
  auto visited = std::vector<bool>(graph.VerticesCount(), false);
  auto vertex_queue = std::queue<size_t>();

  for (size_t i = 0; i < graph.VerticesCount(); ++i) {
    if (!visited[i]) {
      visited[i] = true;
      callback(i);
      vertex_queue.push(i);

      while (!vertex_queue.empty()) {
        size_t current = vertex_queue.front();
        vertex_queue.pop();
        std::vector<size_t> children = graph.GetNextVertices(current);
        for (auto&& child : children) {
          if (!visited[child]) {
            visited[child] = true;
            callback(child);
            vertex_queue.push(child);
          }
        }
      }
    }
  }
}

}  // namespace technopark::algorithms::graph