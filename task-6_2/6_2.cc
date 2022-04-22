/**
 * @file 6_2.cc
 * @author Leonard Pak
 * @brief Дано множество целых чисел из [0..10^9] размера n. Используя алгоритм
 * поиска k-ой порядковой статистики, требуется найти следующие параметры
 * множества: 10%  перцентиль, медиана, 90%  перцентиль.
 * Требования: к дополнительной памяти: O(n). Среднее время работы: O(n). Должна
 * быть отдельно выделенная функция partition. Рекурсия запрещена. Решение
 * должно поддерживать передачу функции сравнения снаружи.
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию
 * Partition реализуйте методом прохода двумя итераторами от конца массива к
 * началу.
 * @version 0.1
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
struct DefaultComparator {
  bool operator()(const T& l, const T& r) const { return (l < r); }
};

template <typename T, typename Comparator = DefaultComparator<T>>
size_t MedianOfThree(T const* arr,
                     size_t const& l,
                     size_t const& r,
                     Comparator cmp = Comparator()) {
  //  Ищем минимальный в каждой паре чисел из 3х, а затем выбираем максимальный
  //  из них. так мы получим средний
  size_t m = l + (r - l) / 2;
  size_t min_1 = cmp(arr[l], arr[r]) ? l : r;
  size_t min_2 = cmp(arr[l], arr[m]) ? l : m;
  size_t min_3 = cmp(arr[m], arr[r]) ? m : r;
  size_t max_1 = cmp(arr[min_1], arr[min_2]) ? min_2 : min_1;
  size_t median = cmp(arr[max_1], arr[min_3]) ? min_3 : max_1;
  return median;
}

template <typename T, typename Comparator = DefaultComparator<T>>
size_t Partition(T* arr,
                 size_t const& l,
                 size_t const& r,
                 Comparator cmp = Comparator()) {
  size_t pivot_idx = MedianOfThree(arr, l, r);

  std::swap(arr[pivot_idx], arr[l]);
  T pivot = arr[l];
  size_t i = r;
  size_t j = i;
  while (j > l) {
    if (cmp(arr[j], pivot)) {
      --j;
    } else {
      if (j != i) {
        std::swap(arr[j], arr[i]);
      }
      --j;
      --i;
    }
  }
  std::swap(arr[i], arr[l]);
  return i;
}

template <typename T>
T KthElement(T* arr, size_t const& size, size_t k) {
  size_t l = 0;
  size_t r = size;
  size_t p = 0;
  do {
    p = Partition(arr, l, r - 1);
    if (p < k) {
      l = p + 1;
    } else {
      r = p;
    }
  } while (p != k);
  return arr[k];
}

void Run(std::istream& in, std::ostream& out);

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "10 1 2 3 4 5 6 7 8 9 10"
       << "\n";
    Run(in, out);
    assert(out.str() == "2\n6\n10\n");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

void Run(std::istream& in, std::ostream& out) {
  size_t size = 0;
  in >> size;
  auto arr = new int[size];
  for (size_t i = 0; i < size; ++i) {
    in >> arr[i];
  }
  size_t element_10 = 0.1 * size;
  size_t element_50 = 0.5 * size;
  size_t element_90 = 0.9 * size;
  out << KthElement(arr, size, element_10) << "\n";
  out << KthElement(arr, size, element_50) << "\n";
  out << KthElement(arr, size, element_90) << "\n";
  delete[] arr;
}

int main() {
  // Run(std::cin, std::cout);
  // std::vector<int> arr = {1, 3, 5, 7, 2, 4, 6, 1, 2, 3};
  // size_t k = 6;
  // KthElement(&arr[0], arr.size(), k);
  // std::cout << "kth element: " << arr[k] << "\n";
  TestContest();
  return 0;
}