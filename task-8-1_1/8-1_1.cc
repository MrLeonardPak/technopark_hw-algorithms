/**
 * @file 8(1)_1.cc
 * @author Леонард Пак
 * @brief Реализуйте структуру данных типа “множество строк” на основе
 * динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и
 * состоят из строчных латинских букв. Хеш-функция строки должна быть
 * реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте
 * при добавлении элементов в случае, когда коэффициент заполнения таблицы
 * достигает 3/4. Структура данных должна поддерживать операции добавления
 * строки в множество, удаления строки из множества и проверки принадлежности
 * данной строки множеству. Для разрешения коллизий используйте квадратичное
 * пробирование. i-ая проба: g(k, i) = g(k, i-1) + i (mod m) -- m - степень
 * двойки.
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

size_t StrHash(std::string const& data) {
  size_t hash = 0;
  for (char i : data) {
    hash = hash * 13 + i;
  }
  return hash;
}

static constexpr size_t kBucketsCount[] = {7,   17,   37,   73,   149,  251,
                                           509, 1021, 2027, 5003, 10837};

template <typename T>
struct Hash;

template <>
struct Hash<std::string> {
  size_t operator()(std::string const& str) const { return StrHash(str); }
};

template <typename T>
struct Equal {
  bool operator()(T const& l, T const& r) const { return l == r; }
};

template <typename Key, typename Hash = Hash<Key>, typename Equal = Equal<Key>>
class HashSet {
 public:
  HashSet(Hash hash = Hash(), Equal equal = Equal())
      : buffer_(nullptr),
        items_count_(0),
        buckets_count_(0),
        size_idx_(0),
        hash_(hash),
        equal_(equal) {}

  ~HashSet() {
    for (size_t i = 0; i < buckets_count_; ++i) {
      Node* cur = buffer_[i];
      while (cur != nullptr) {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
      }
    }
    delete[] buffer_;
  }

  bool Find(Key const& key) const {
    if (buffer_ == nullptr) {
      return false;
    }

    size_t bucket_idx = hash_(key) % buckets_count_;
    Node* cur = buffer_[bucket_idx];
    while (cur != nullptr) {
      if (equal_(key, cur->key)) {
        return true;
      }
      cur = cur->next;
    }

    return false;
  }

  bool Insert(Key const& key) {
    if (Find(key)) {
      return false;  // Дубликаты запрещены
    }

    if ((buffer_ == nullptr) ||
        (items_count_ > buckets_count_ * kMaxLoadFactor)) {
      Grow();
    }

    size_t bucket_idx = hash_(key) % buckets_count_;
    buffer_[bucket_idx] = new Node(buffer_[bucket_idx], key);
    ++items_count_;
    return true;
  }

  bool Erase(Key const& key) {
    if (buffer_ == nullptr) {
      return false;
    }

    size_t bucket_idx = hash_(key) % buckets_count_;
    Node* cur = buffer_[bucket_idx];
    Node** prev = &buffer_[bucket_idx];
    while (cur != nullptr) {
      if (equal_(key, cur->key)) {
        *prev = cur->next;
        --items_count_;
        delete cur;
        return true;
      }
      prev = &cur->next;
      cur = cur->next;
    }

    return false;
  }

  bool Is_Empty() const { return items_count_ == 0; }
  size_t get_size() const { return items_count_; }

 private:
  struct Node {
    Node* next;
    Key key;

    Node(Node* next, Key const& key) : next(next), key(key) {}
  };

  Node** buffer_;
  size_t items_count_;
  size_t buckets_count_;
  size_t size_idx_;
  Hash hash_;
  Equal equal_;
  static constexpr size_t kMaxLoadFactor = 7;

  void Grow() {
    Node** old_buffer = buffer_;
    size_t old_buckets_count = buckets_count_;

    buckets_count_ = kBucketsCount[size_idx_++];
    buffer_ = new Node*[buckets_count_];

    for (size_t i = 0; i < buckets_count_; ++i) {
      buffer_[i] = nullptr;
    }

    for (size_t i = 0; i < old_buckets_count; ++i) {
      Node* cur = old_buffer[i];
      while (cur != nullptr) {
        size_t bucket_idx = hash_(cur->key) % buckets_count_;
        Node* tmp = cur;
        cur = cur->next;

        tmp->next = buffer_[bucket_idx];
        buffer_[bucket_idx] = tmp;
      }

      delete[] old_buffer;
    }
  }
};

void Run(std::istream& in, std::ostream& out) {
  static constexpr char kSuccess[] = "OK";
  static constexpr char kFail[] = "FAIL";

  char operation = 0;
  std::string key;
  HashSet<std::string> hash_set;

  while (in >> operation >> key) {
    switch (operation) {
      case '+':
        out << ((hash_set.Insert(key)) ? kSuccess : kFail) << "\n";
        break;
      case '-':
        out << ((hash_set.Erase(key)) ? kSuccess : kFail) << "\n";
        break;
      case '?':
        out << ((hash_set.Find(key)) ? kSuccess : kFail) << "\n";
        break;
      default:
        assert(false);
        break;
    }
  }
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "+ hello + bye ? bye + bye - bye ? bye ? hello";
    Run(in, out);
    assert(out.str() == "OK\nOK\nOK\nFAIL\nOK\nFAIL\nOK\n");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  // Run(std::cin, std::cout);
  TestContest();
  return 0;
}