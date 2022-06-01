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
#include <vector>

template <typename T>
struct Hash;

template <>
struct Hash<std::string> {
  size_t operator()(std::string const& str) const {
    size_t hash = 0;
    for (char c : str) {
      hash = hash * 137 + c;
    }
    return hash;
  }
};

template <typename T>
struct Equal {
  bool operator()(T const& l, T const& r) const { return l == r; }
};

template <typename Key, typename Hash = Hash<Key>, typename Equal = Equal<Key>>
class HashSet {
 public:
  HashSet(Hash hash = Hash(), Equal equal = Equal())
      : hasher_(hash), equal_(equal) {}

  HashSet(HashSet const&) = delete;
  HashSet(HashSet&&) = delete;

  HashSet& operator=(HashSet const&) = delete;
  HashSet& operator=(HashSet&&) = delete;

  ~HashSet() = default;

  bool Find(Key const& key) const {
    if (buffer_.empty()) {
      return false;
    }

    size_t hash = hasher_(key) % buffer_.size();
    for (size_t i = 0; i < buffer_.size(); ++i) {
      Item item = buffer_[hash];
      switch (item.state) {
        case Item::BUSY:
          if (item.key == key) {
            return true;
          }
          break;
        case Item::EMPTY:
          return false;
        default:
          break;
      }
      // Квадратичное пробирование
      hash = (hash + i) % buffer_.size();
    }

    return false;
  }

  bool Insert(Key const& key) {
    if ((buffer_.empty()) || (items_count_ >= kFillFactor * buffer_.size())) {
      Grow();
    }

    size_t abs_hash = hasher_(key);
    size_t hash = abs_hash % buffer_.size();
    size_t del_idx = buffer_.size();
    for (size_t i = 0; i < buffer_.size(); ++i) {
      Item& item = buffer_[hash];
      switch (item.state) {
        case Item::BUSY:
          if (item.key == key) {
            return false;
          }
          break;
        case Item::EMPTY:
          if (del_idx == buffer_.size()) {
            item = Item(key, abs_hash);
          } else {
            buffer_[del_idx] = Item(key, abs_hash);
          }
          ++items_count_;
          return true;
        case Item::DEL:
          del_idx = (del_idx == buffer_.size()) ? hash : del_idx;
          break;
        default:
          break;
      }
      // Квадратичное пробирование
      hash = (hash + i) % buffer_.size();
    }
    // Тк делается перехэширование по items_count_, а он хранит количество
    // существующих элементов (BUSY+DEL), то сюда дойти теоритически невозможно
    // (тк будет перехеширование), поэтому лучше выкинуть исключение
    throw std::logic_error(
        "Прошли весь цикл при добавление, а место не нашли!");
  }

  bool Erase(Key const& key) {
    if (buffer_.empty()) {
      return false;
    }

    size_t hash = hasher_(key) % buffer_.size();
    for (size_t i = 0; i < buffer_.size(); ++i) {
      Item& item = buffer_[hash];
      switch (item.state) {
        case Item::BUSY:
          if (item.key == key) {
            item.state = Item::DEL;
            ++del_items_count_;
            return true;
          }
          break;
        case Item::EMPTY:
          return false;
        case Item::DEL:
          break;
        default:
          break;
      }
      // Квадратичное пробирование
      hash = (hash + i) % buffer_.size();
    }
    return false;
  }

 private:
  struct Item {
    Key key;
    size_t hash;
    enum State { EMPTY, BUSY, DEL } state;

    Item() = default;

    Item(Key const& key, size_t const& hash)
        : key(key), hash(hash), state(BUSY) {}
  };

  std::vector<Item> buffer_;
  size_t items_count_ = 0;
  size_t del_items_count_ = 0;
  Hash hasher_;
  Equal equal_;
  size_t constexpr static kMaxLoadFactor = 7;
  size_t constexpr static kStartSize = 8;
  float constexpr static kFillFactor = 0.75;

  void Grow() {
    if (buffer_.empty()) {
      buffer_.resize(kStartSize);
      return;
    }

    size_t new_size = buffer_.size() * 2;
    std::vector<Item> new_buffer(new_size);
    for (size_t i = 0; i < buffer_.size(); ++i) {
      if (buffer_[i].state == Item::BUSY) {
        size_t new_hash = buffer_[i].hash % new_size;
        // Ищем место по новому хешу
        size_t hash = new_hash;
        for (size_t i = 0;
             (i < new_size) && (new_buffer[hash].state == Item::BUSY); ++i) {
          // Квадратичное пробирование
          hash = (hash + i) % new_size;
        }
        new_hash = hash;

        new_buffer[new_hash] = buffer_[i];
      }
    }

    buffer_ = std::move(new_buffer);
    items_count_ -= del_items_count_;
    del_items_count_ = 0;
  }
};

void Run(std::istream& in, std::ostream& out) {
  char constexpr static kSuccess[] = "OK";
  char constexpr static kFail[] = "FAIL";

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