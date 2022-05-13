/**
 * @file 9-2_4.cc
 * @author Leonard Pak
 * @brief
 * @version 0.1
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cassert>
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
  };

 public:
  Tree(Comparator comp = Comparator()) : comp_(comp) {}
  ~Tree() = default;

  void Push(T const& value) {
    if (root_ == nullptr) {
      root_ = new Node<T>{.value = value};
      return;
    }
    }

  void LevelOrder() {
    if (root_ == nullptr) {
      return;
    }

    auto nodes = std::queue<Node*>();
    nodes.push(root_);
    while (!nodes.empty()) {
      Node* tmp_node = nodes.front();
      nodes.pop();
      nodes.std::cout << tmp_node->value << '\n';
      if (tmp_node->left != nullptr) {
        nodes.push(tmp_node->left);
      }
      if (tmp_node->right != nullptr) {
        nodes.push(tmp_node->right);
      }
    }
  }

 private:
  Node* root_ = nullptr;
  size_t size_ = 0;
  Comparator comp_;
};

void Run(std::istream& in, std::ostream& out) {
  size_t n = 0;
  in >> n;
  auto tree = Tree<int>();
  for (size_t i = 0; i < n; ++i) {
  }
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 2 1 3" << std::endl;
    Run(in, out);
    assert(out.str() == "2 1 3");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 1 2 3" << std::endl;
    Run(in, out);
    assert(out.str() == "1 2 3");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 3 1 2" << std::endl;
    Run(in, out);
    assert(out.str() == "3 1 2");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "4 3 1 4 2" << std::endl;
    Run(in, out);
    assert(out.str() == "3 1 4 2");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "10 10 5 4 7 9 8 6 3 2 1" << std::endl;
    Run(in, out);
    assert(out.str() == "10 5 4 7 3 6 9 2 8 1");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "10 9 8 6 10 4 3 2 5 1 7" << std::endl;
    Run(in, out);
    assert(out.str() == "9 8 10 6 4 7 3 5 2 1");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "10 1 7 10 9 4 3 8 5 2 6" << std::endl;
    Run(in, out);
    assert(out.str() == "1 7 4 10 3 5 9 2 6 8");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  Run(std::cin, std::cout);
  return 0;
}