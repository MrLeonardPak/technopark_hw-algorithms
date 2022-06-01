/**
 * @file 11-4_2.cc
 * @author Leonard Pak
 * @brief Дано число N и N строк. Каждая строка содержит команду добавления или
 * удаления натуральных чисел, а также запрос на получение k-ой порядковой
 * статистики. Команда добавления числа A задается положительным числом A,
 * команда удаления числа A задается отрицательным числом “-A”. Запрос на
 * получение k-ой порядковой статистики задается числом k. Требования: скорость
 * выполнения запроса - O(log n).
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
  int operator()(T const& l, T const& r) {
    if (l < r) {
      return -1;
    }
    if (l > r) {
      return 1;
    }
    return 0;
  }
};

template <typename Key, typename Comparator = DefaultComparator<Key>>
class AvlTree {
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Key key{};
    size_t node_count = 1;
    uint8_t height = 1;

    Node(Key const& key) : key(key) {}

    Node(Node const&) = delete;
    Node& operator=(Node const&) = delete;

    ~Node() = default;
  };

 public:
  AvlTree(Comparator comp = Comparator()) : comp_(comp) {}

  AvlTree(AvlTree const&) = delete;
  AvlTree& operator=(AvlTree const&) = delete;

  ~AvlTree() {
    auto delete_lambda = [](Node* node) { delete node; };
    LevelOrder(delete_lambda);
  }

  void Insert(Key const& key) { root_ = InsertAux(key, root_); }

  Key GetKth(size_t const& kth) { return GetKthAux(kth, root_); }

  void Erase(Key const& key) { root_ = EraseAux(key, root_); }

 private:
  Node* root_ = nullptr;
  Comparator comp_;

  Node* InsertAux(Key const& key, Node* node) {
    if (node == nullptr) {
      return new Node(key);
    }
    int cmp_res = comp_(key, node->key);
    if (cmp_res == -1) {  // <
      node->left = InsertAux(key, node->left);
    } else if (cmp_res == 1) {  // >
      node->right = InsertAux(key, node->right);
    }
    return Balance(node);
  }

  Node* EraseAux(Key const& key, Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    int cmp_res = comp_(key, node->key);
    if (cmp_res == -1) {  // <
      node->left = EraseAux(key, node->left);
    } else if (cmp_res == 1) {  // >
      node->right = EraseAux(key, node->right);
    } else {  // =
      Node* left = node->left;
      Node* right = node->right;
      delete node;

      if (right == nullptr) {
        return left;
      }

      Node* min_node = FindAndRemoveMin(right);
      min_node->left = left;
      return Balance(min_node);
    }
    return Balance(node);
  }

  Node* FindMinChild(Node* node) {
    // Необходимо вручную уменьшить число, тк не каждаю их нод пройдет
    // балансировку
    --node->node_count;
    Node* child_node = node->left;
    return (child_node->left == nullptr) ? node : FindMinChild(child_node);
  }

  Node* FindAndRemoveMin(Node* node) {
    Node* min_node = nullptr;
    if (node->left != nullptr) {
      // Ищем ноду, чей левый ребенок минимальный
      Node* prev_node = FindMinChild(node);
      min_node = prev_node->left;
      // Удаляем минимальную ноду
      prev_node->left = min_node->right;
      // Поднимаем наверх минимальную ноду
      min_node->right = node;
    } else {
      min_node = node;
    }
    return min_node;
  }

  uint8_t Height(Node* node) { return (node == nullptr) ? 0 : node->height; }

  size_t NodeCount(Node* node) {
    return (node == nullptr) ? 0 : node->node_count;
  }

  void Fix(Node* node) {
    node->height = std::max(Height(node->left), Height(node->right)) + 1;
    node->node_count = NodeCount(node->left) + NodeCount(node->right) + 1;
  }

  int BalanceFactor(Node* node) {
    return Height(node->right) - Height(node->left);
  }

  Node* RotateLeft(Node* node) {
    Node* right = node->right;
    node->right = right->left;
    right->left = node;

    Fix(node);
    Fix(right);

    return right;
  }

  Node* RotateRight(Node* node) {
    Node* left = node->left;
    node->left = left->right;
    left->right = node;

    Fix(node);
    Fix(left);

    return left;
  }

  Node* Balance(Node* node) {
    Fix(node);

    int bf = BalanceFactor(node);
    if (bf == 2) {
      if (BalanceFactor(node->right) < 0) {
        node->right = RotateRight(node->right);
      }
      return RotateLeft(node);
    } else if (bf == -2) {
      if (BalanceFactor(node->left) > 0) {
        node->left = RotateLeft(node->left);
      }
      return RotateRight(node);
    }
    return node;
  }

  Key GetKthAux(size_t const& kth, Node* node) {
    size_t left_children_count = NodeCount(node->left);
    if (left_children_count > kth) {
      return GetKthAux(kth, node->left);
    }
    if (left_children_count < kth) {
      return GetKthAux(kth - (left_children_count + 1), node->right);
    }
    return node->key;
  }

  void LevelOrder(std::function<void(Node*)> execution) {
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
  auto avl_tree = AvlTree<int>();
  for (size_t i = 0; i < n; ++i) {
    int a, b;
    in >> a >> b;
    if (a > 0) {
      avl_tree.Insert(a);
    } else {
      avl_tree.Erase(a * (-1));
    }
    out << avl_tree.GetKth(b) << ' ';
  }
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 1 0 2 0 -1 0 " << std::endl;
    Run(in, out);
    assert(out.str() == "1 1 2 ");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "5 40 0 10 1 4 1 -10 0 50 2" << std::endl;
    Run(in, out);
    assert(out.str() == "40 40 10 4 50 ");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  TestContest();
  // Run(std::cin,  std::cout);
  return 0;
}