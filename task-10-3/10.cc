/**
 * @file 10.cc
 * @author Leonard Pak
 * @brief Постройте B-дерево минимального порядка t и выведите его по слоям. В
 * качестве ключа используются числа, лежащие в диапазоне 0..232 -1.
 * B-дереводолжно быть реализовано в виде шаблонного класса. Решение должно
 * поддерживать передачу функции сравнения снаружи. Формат входных данных
 * Сначала вводится минимальный порядок дерева t. Затем вводятся элементы
 * дерева. Формат выходных данных Программа должна вывести B-дерево по слоям.
 * Каждый слой на новой строке, элементы должны выводится в том порядке, в
 * котором они лежат в узлах.
 * @version 0.1
 * @date 2022-05-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

template <typename T>
struct DefaultComparator {
  bool operator()(const T& l, const T& r) const { return (l < r); }
};

template <typename Key, typename Comparator = DefaultComparator<Key>>
class BTree {
  struct Node {
    bool leaf = false;
    std::vector<Key> keys;
    std::vector<Node*> children;

    Node(bool is_leaf) : leaf(is_leaf) {}
    // TODO
    ~Node() {
      for (auto node : children) {
        delete node;
      }
    }
  };

 public:
  BTree(size_t min_degree, Comparator comp = Comparator())
      : t_(min_degree), comp_(comp) {}
  // TODO
  ~BTree() { delete root_; }

  bool Find(Key const& key) { return FindAux(key, root_); }

  void Insert(Key const& key) {
    if (root_ == nullptr) {
      root_ = new Node(true);
    }

    if (IsFull(root_)) {
      Node* node = new Node(false);
      node->children.push_back(root_);
      root_ = node;
      Split(root_, 0);
    }

    InsertAux(key, root_);
  }

  void Print(std::ostream& out) {
    if (root_ == nullptr) {
      return;
    }

    auto nodes = std::queue<Node*>();
    nodes.push(root_);
    while (!nodes.empty()) {
      auto tmp_nodes = std::queue<Node*>();
      while (!nodes.empty()) {
        Node* node = nodes.front();
        nodes.pop();

        for (auto const& key : node->keys) {
          out << key << ' ';
        }

        for (Node* child : node->children) {
          tmp_nodes.push(child);
        }
      }
      out << '\n';
      nodes = tmp_nodes;
    }
  }

 private:
  Node* root_ = nullptr;
  size_t t_;
  Comparator comp_;

  void Split(Node* node, size_t idx) {
    // y - переполненая нода нода, z - новыя нода
    auto y_node = node->children[idx];
    auto z_node = new Node(y_node->leaf);
    z_node->keys.resize(t_ - 1);

    for (size_t j = 0; j < t_ - 1; ++j) {
      z_node->keys[j] = y_node->keys[j + t_];
    }

    if (!y_node->leaf) {
      z_node->children.resize(t_);
      for (size_t j = 0; j < t_; ++j) {
        z_node->children[j] = y_node->children[j + t_];
      }
      y_node->children.resize(t_);
    }

    node->children.resize(node->children.size() + 1);
    for (size_t j = node->children.size() - 1; j > idx + 1; --j) {
      node->children[j] = node->children[j - 1];
    }
    node->children[idx + 1] = z_node;

    node->keys.resize(node->keys.size() + 1);
    for (size_t j = node->keys.size() - 1; j > idx + 1; --j) {
      node->keys[j] = node->keys[j - 1];
    }
    node->keys[idx] = y_node->keys[t_ - 1];

    y_node->keys.resize(t_ - 1);
  }

  bool FindAux(Key const& key, Node* node) {
    int i = 0;
    while ((i < node->keys.size() && (key > node->keys[i]))) {
      ++i;
    }
    if ((i < node->keys.size()) && (key == node->keys[i])) {
      return true;
    } else if (node->leaf) {
      return false;
    } else {
      return FindAux(key, node->children[i]);
    }
  }

  void InsertAux(Key const& key, Node* node) {
    int pos = node->keys.size() - 1;
    if (node->leaf) {
      node->keys.resize(node->keys.size() + 1);
      while ((pos >= 0) && (key < node->keys[pos])) {
        node->keys[pos + 1] = node->keys[pos];
        --pos;
      }
      node->keys[pos + 1] = key;
    } else {
      while ((pos >= 0) && (key < node->keys[pos])) {
        --pos;
      }
      if (IsFull(node->children[pos + 1])) {
        Split(node, pos + 1);
        if (key > node->keys[pos + 1]) {
          ++pos;
        }
      }
      InsertAux(key, node->children[pos + 1]);
    }
  }

  bool IsFull(Node* node) const { return (2 * t_ - 1) == node->keys.size(); }
};

void Run(std::istream& in, std::ostream& out) {
  size_t n = 0;
  in >> n;
  auto b_tree = BTree<int>(n);
  int key = 0;
  while (in >> key) {
    b_tree.Insert(key);
  }
  b_tree.Print(out);
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "2 0 1 2 3 4 5 6 7 8 9" << std::endl;
    Run(in, out);
    assert(out.str() == "3 \n1 5 7 \n0 2 4 6 8 9 \n");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "4 0 1 2 3 4 5 6 7 8 9" << std::endl;
    Run(in, out);
    assert(out.str() == "3 \n0 1 2 4 5 6 7 8 9 \n");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  TestContest();
  // Run(std::cin, std::cout);
  return 0;
}