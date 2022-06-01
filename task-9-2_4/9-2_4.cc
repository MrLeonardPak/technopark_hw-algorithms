/**
 * @file 9-2_4.cc
 * @author Leonard Pak
 * @brief Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31]
 * длиной N. Требуется построить бинарное дерево, заданное наивным порядком
 * вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если
 * root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое
 * поддерево root. Требования: Рекурсия запрещена. Решение должно поддерживать
 * передачу функции сравнения снаружи.
 * @version 0.1
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>

template <typename T>
struct DefaultComparator {
  bool operator()(T const& l, T const& r) { return l < r; }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Tree {
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    T value = {};
    Node(T const& val) : value(val) {}
    ~Node() = default;
  };

 public:
  Tree(Comparator comp = Comparator()) : comp_(comp) {}

  Tree(Tree const&) = delete;
  Tree& operator=(Tree const&) = delete;

  ~Tree() {
    auto delete_lambda = [](Node* node) { delete node; };
    LevelOrderAux(delete_lambda);
  }

  void Insert(T const& value) {
    Node* node = root_;
    Node* parent = nullptr;
    while (node != nullptr) {
      parent = node;
      if (comp_(value, node->value)) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    node = new Node(value);
    if (parent == nullptr) {
      root_ = node;
    } else {
      if (comp_(node->value, parent->value)) {
        parent->left = node;
      } else {
        parent->right = node;
      }
    }
  }

  void LevelOrder(std::function<void(T const&)> execution) {
    LevelOrderAux([execution](Node* node) { execution(node->value); });
  }

 private:
  Node* root_ = nullptr;
  size_t size_ = 0;
  Comparator comp_;

  void LevelOrderAux(std::function<void(Node*)> execution) {
    if (root_ == nullptr) {
      return;
    }

    auto nodes = std::queue<Node*>();
    nodes.push(root_);
    while (!nodes.empty()) {
      Node* tmp_node = nodes.front();
      nodes.pop();
      if (tmp_node->left != nullptr) {
        nodes.push(tmp_node->left);
      }
      if (tmp_node->right != nullptr) {
        nodes.push(tmp_node->right);
      }
      execution(tmp_node);
    }
  }
};

void Run(std::istream& in, std::ostream& out) {
  size_t n = 0;
  in >> n;
  auto tree = Tree<int>();
  for (size_t i = 0; i < n; ++i) {
    int a = 0;
    in >> a;
    tree.Insert(a);
  }
  auto out_lambda = [&out](int const& value) { out << value << ' '; };
  tree.LevelOrder(out_lambda);
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 2 1 3" << std::endl;
    Run(in, out);
    assert(out.str() == "2 1 3 ");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 1 2 3" << std::endl;
    Run(in, out);
    assert(out.str() == "1 2 3 ");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 3 1 2" << std::endl;
    Run(in, out);
    assert(out.str() == "3 1 2 ");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "4 3 1 4 2" << std::endl;
    Run(in, out);
    assert(out.str() == "3 1 4 2 ");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "10 10 5 4 7 9 8 6 3 2 1" << std::endl;
    Run(in, out);
    assert(out.str() == "10 5 4 7 3 6 9 2 8 1 ");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "10 9 8 6 10 4 3 2 5 1 7" << std::endl;
    Run(in, out);
    assert(out.str() == "9 8 10 6 4 7 3 5 2 1 ");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "10 1 7 10 9 4 3 8 5 2 6" << std::endl;
    Run(in, out);
    assert(out.str() == "1 7 4 10 3 5 9 2 6 8 ");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  TestContest();
  // Run(std::cin, std::cout);
  return 0;
}