/**
 * @file 4_3.cc
 * @author Leonard Pak
 * @brief Решение предполагает использование кучи, реализованной в виде
 * шаблонного класса. Решение должно поддерживать передачу функции сравнения
 * снаружи. Куча должна быть динамической.
 * В операционной системе Technux есть планировщик процессов. Каждый процесс
 * характеризуется: приоритетом P, временем, которое он уже отработал t,
 * временем, которое необходимо для завершения работы процесса T. Планировщик
 * процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его
 * время P и кладет обратно в очередь процессов. Если выполняется условие t >=
 * T, то процесс считается завершенным и удаляется из очереди. Требуется
 * посчитать кол-во переключений процессора. Формат входных данных: Сначала
 * вводится кол-во процессов. После этого процессы в формате P T. Формат
 * выходных данных: Кол-во переключений процессора.
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cassert>
#include <iostream>

// XXX: Объявления

template <typename T>
class DynamicArray {
 public:
  DynamicArray(size_t start_size);

  DynamicArray(DynamicArray const&) = delete;
  DynamicArray(DynamicArray&&) = delete;

  DynamicArray& operator=(DynamicArray const&) = delete;
  DynamicArray& operator=(DynamicArray&&) = delete;

  ~DynamicArray();

  T& operator[](int index);

  size_t MaxSize() const { return max_size_; }

 private:
  const size_t kStartSize;
  const int kReallocMultiplication;

  size_t size_;
  size_t max_size_;
  T* dynamic_array;

  void Reallocation();
};

template <typename T>
struct DefaultComparator {
  bool operator()(T const& l, T const& r) const { return l < r; }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Heap {
 public:
  Heap(Comparator comp = Comparator());

  Heap(Heap const&) = delete;
  Heap(Heap&&) = delete;

  Heap& operator=(Heap const&) = delete;
  Heap& operator=(Heap&&) = delete;

  ~Heap();

  T const& Top() const;
  void Pop();

  void Push(T const&);

  bool IsEmpty() const;
  size_t Size() const;

 private:
  T* buf;
  size_t buffer_size;
  size_t heap_size;
};

// XXX: Определения

template <typename T>
DynamicArray<T>::DynamicArray(size_t start_size) {}

void TestDynamicArray() {
  DynamicArray<int> arr(2);
  for (size_t i = 0; i < 10; ++i) {
    arr[i] = i;
  }
  assert(arr.MaxSize() == 16);
}

int main() {
  TestDynamicArray();
  return 0;
}