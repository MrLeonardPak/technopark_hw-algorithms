#include "list_graph.h"

#include <iostream>

namespace graph = ::technopark::algorithms::graph;

void Run() {
  auto print_out = [](size_t v) { std::cout << v << "  "; };

  auto list_graph = graph::ListGraph(6);

  list_graph.AddEdge(0, 1);
  list_graph.AddEdge(0, 2);
  list_graph.AddEdge(1, 2);
  list_graph.AddEdge(1, 3);
  list_graph.AddEdge(3, 4);
  list_graph.AddEdge(3, 5);
  list_graph.AddEdge(2, 5);

  std::cout << "List Graph: ";
  graph::IGraph::DFS(list_graph, 0, print_out);
  std::cout << std::endl;
  graph::IGraph::BFS(list_graph, 0, print_out);
  std::cout << std::endl;
}

int main() {
  Run();

  return 0;
}