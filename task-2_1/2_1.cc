#include <iostream>

int ExpSearch(int const* arr,
              size_t size,
              int target_num,
              size_t& out_end_batch) {
  size_t end_batch = 1;
  for (; end_batch <= size; end_batch *= 2) {
    if (arr[end_batch - 1] >= target_num) {
      out_end_batch = end_batch;
      return 0;
    }
  }
  return -1;
}

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

int main() {
  int a_size = 0;
  int b_size = 0;
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
    size_t end_batch = 0;
    size_t min_index = 0;
    if (ExpSearch(a_arr, a_size, b_arr[i], end_batch) ||
        (BinarySearch(a_arr + end_batch / 2, end_batch - end_batch / 2,
                      b_arr[i], min_index))) {
      std::cout << a_size << " ";
    } else {
      std::cout << min_index + end_batch / 2 << " ";
    }
  }

  delete[] a_arr;
  delete[] b_arr;
  return 0;
}