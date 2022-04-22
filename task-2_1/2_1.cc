/**
 * @file 2_1.cc
 * @author Leonard Pak
 * @brief Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел
 * B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k
 * минимального элемента массива A, равного или превосходящего B[i]: A[k] >=
 * B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000. Требования: Время
 * работы поиска k для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче
 * для каждого B[i] сначала нужно определить диапазон для бинарного поиска
 * размером порядка k с помощью экспоненциального поиска, а потом уже в нем
 * делать бинарный поиск.
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

int BinarySearch(int const* arr,
                 size_t size,
                 int target_num,
                 size_t& out_min_index) {
  size_t start_batch = 0;
  size_t end_batch = size;
  while (start_batch < end_batch) {
    size_t mid = (end_batch + start_batch) / 2;
    if (arr[mid] < target_num) {
      start_batch = mid + 1;
    } else {
      end_batch = mid;
    }
  }
  if (start_batch == size) {
    return -1;
  }
  out_min_index = start_batch;
  return 0;
}

int ExpSearch(int const* arr,
              size_t size,
              int target_num,
              size_t& out_min_index) {
  size_t end_batch = 1;
  while ((end_batch < size) && (arr[end_batch - 1] < target_num)) {
    end_batch *= 2;
  }
  size_t shift = end_batch / 2;
  size_t batch_size = std::min(size, end_batch) - shift;
  if (BinarySearch(arr + shift, batch_size, target_num, out_min_index)) {
    return -1;
  }
  out_min_index += shift;
  return 0;
}

int main() {
  size_t a_size = 0;
  size_t b_size = 0;
  std::cin >> a_size >> b_size;
  int* a_arr = new int[a_size];
  int* b_arr = new int[b_size];
  for (size_t i = 0; i < a_size; ++i) {
    std::cin >> a_arr[i];
  }
  for (size_t i = 0; i < b_size; ++i) {
    std::cin >> b_arr[i];
  }

  for (size_t i = 0; i < b_size; ++i) {
    size_t min_index = 0;
    if (ExpSearch(a_arr, a_size, b_arr[i], min_index)) {
      std::cout << a_size << std::endl;
    } else {
      std::cout << min_index << std::endl;
    }
  }

  delete[] a_arr;
  delete[] b_arr;
  return 0;
}