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
#include <iostream>
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

template <typename Key,
          typename Value,
          typename Comparator = DefaultComparator<Value>>
class AvlTree {
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Key key{};
    Value value{};
    uint8_t height = 1;

    Node(Key const& key, Value const& value) : key(key), value(value) {}

    Node(Node const&) = delete;
    Node& operator=(Node const&) = delete;

    ~Node() {
      // // TODO: убрать рекурсию
      // delete left;
      // delete right;
    }
  };

 public:
  AvlTree(Comparator comp = Comparator()) : comp_(comp) {}

  AvlTree(AvlTree const&) = delete;
  AvlTree& operator=(AvlTree const&) = delete;

  ~AvlTree() {
    // // TODO: убрать рекурсию
    // delete root_;
  }

  Value* Find(Key const& key) { return FindAux(key, root_); }

  void Insert(Key const& key, Value const& value) {
    root_ = InsertAux(key, value, root_);
  }

  void Erase(Key const& key) { root_ = EraseAux(key, root_); }

 private:
  Node* root_ = nullptr;
  Comparator comp_;

  Value* FindAux(Key const& key, Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    int cmp_res = comp_(key, node->key);
    if (cmp_res == -1) {  // <
      return FindAux(key, node->left);
    }
    if (cmp_res == 1) {  // >
      return FindAux(key, node->right);
    }
    return &node->value;
  }

  Node* InsertAux(Key const& key, Value const& value, Node* node) {
    if (node == nullptr) {
      return new Node(key, value);
    }
    int cmp_res = comp_(key, node->key);
    if (cmp_res == -1) {  // <
      node->left = InsertAux(key, value, node->left);
    } else if (cmp_res == 1) {  // >
      node->right = InsertAux(key, value, node->right);
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

      // TODO: Сделать вместо FindMin + RemoveMin одну функцию FindAndRemoveMin
      Node* min_node = FindMin(right);
      min_node->right = RemoveMin(right);
      min_node->left = left;
      return Balance(min_node);
    }
    return Balance(node);
  }

  Node* FindMin(Node* node) {
    if (node->left == nullptr) {
      return node;
    }
    return FindMin(node->left);
  }

  Node* RemoveMin(Node* node) {
    if (node->left == nullptr) {
      return node->right;
    }
    node->left = RemoveMin(node->left);
    return Balance(node);
  }

  uint8_t Height(Node* node) { return (node == nullptr) ? 0 : node->height; }

  void FixHeight(Node* node) {
    // TODO: хранить информацию о k-порядковой статистике и обновлять её тут
    node->height = std::max(Height(node->left), Height(node->right)) + 1;
  }

  int BalanceFactor(Node* node) {
    return Height(node->right) * Height(node->left);
  }

  Node* RotateLeft(Node* node);
  Node* RotateRight(Node* node);

  Node* Balance(Node* node) {
    FixHeight(node);

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
  }
};

void Run(std::istream& in, std::ostream& out) {
  size_t n = 0;
  in >> n;
  // auto avl_tree = AvlTree<>();
  for (size_t i = 0; i < n; ++i) {
    /* code */
  }
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "5 40 0 10 1 4 1 -10 0 50 2" << std::endl;
    Run(in, out);
    assert(out.str() == "40 40 10 4 50");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  TestContest();
  // Run(std::cin, std::cout);
  return 0;
}