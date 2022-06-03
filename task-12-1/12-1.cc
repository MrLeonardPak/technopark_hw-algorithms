/**
 * @file 12-1.cc
 * @author Leonard Pak
 * @brief Необходимо написать несколько реализаций интерфейса:
 * ListGraph, хранящий граф в виде массива списков смежности,
 * MatrixGraph, хранящий граф в виде матрицы смежности,
 * SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев
 * поиска,
 * ArcGraph, хранящий граф в виде одного массива пар {from, to}.
 * @version 0.1
 * @date 2022-06-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "arc_graph.h"
#include "list_graph.h"
#include "matrix_graph.h"
#include "set_graph.h"

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

  std::cout << "List Graph:" << std::endl;
  std::cout << "DFS: ";
  graph::IGraph::DFS(list_graph, 0, print_out);
  std::cout << std::endl;
  std::cout << "BFS: ";
  graph::IGraph::BFS(list_graph, 0, print_out);
  std::cout << std::endl;

  auto list_graph_copy = graph::ListGraph(list_graph);
  std::cout << "List Graph Copy:" << std::endl;
  std::cout << "DFS: ";
  graph::IGraph::DFS(list_graph_copy, 0, print_out);
  std::cout << std::endl;
  std::cout << "BFS: ";
  graph::IGraph::BFS(list_graph_copy, 0, print_out);
  std::cout << std::endl;

  auto matrix_graph = graph::MatrixGraph(list_graph);
  std::cout << "Matrix Graph:" << std::endl;
  std::cout << "DFS: ";
  graph::IGraph::DFS(matrix_graph, 0, print_out);
  std::cout << std::endl;
  std::cout << "BFS: ";
  graph::IGraph::BFS(matrix_graph, 0, print_out);
  std::cout << std::endl;

  auto set_graph = graph::SetGraph(list_graph);
  std::cout << "Set Graph:" << std::endl;
  std::cout << "DFS: ";
  graph::IGraph::DFS(set_graph, 0, print_out);
  std::cout << std::endl;
  std::cout << "BFS: ";
  graph::IGraph::BFS(set_graph, 0, print_out);
  std::cout << std::endl;

  auto arc_graph = graph::ArcGraph(list_graph);
  std::cout << "Arc Graph:" << std::endl;
  std::cout << "DFS: ";
  graph::IGraph::DFS(arc_graph, 0, print_out);
  std::cout << std::endl;
  std::cout << "BFS: ";
  graph::IGraph::BFS(arc_graph, 0, print_out);
  std::cout << std::endl;
}

int main() {
  Run();

  return 0;
}