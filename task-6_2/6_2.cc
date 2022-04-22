#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
struct DefaultComparator {
  bool operator()(const T& l, const T& r) const { return (l < r); }
};

template <typename T, typename Comparator = DefaultComparator<T>>
size_t Partition(T* arr,
                 size_t const& l,
                 size_t const& r,
                 Comparator cmp = Comparator()) {
  size_t m = l + (r - l) / 2;
  size_t min_1 = cmp(arr[l], arr[r]) ? l : r;
  size_t min_2 = cmp(arr[l], arr[m]) ? l : m;
  size_t min_3 = cmp(arr[m], arr[r]) ? m : r;
  size_t max_1 = cmp(arr[min_1], arr[min_2]) ? min_2 : min_1;
  size_t max_2 = cmp(arr[max_1], arr[min_3]) ? min_3 : max_1;

  size_t pivot_idx = max_2;

  std::swap(arr[pivot_idx], arr[l]);
  T pivot = arr[l];
  size_t i = r - 1;
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
void KthElement(T* arr, size_t const& size, size_t k) {
  size_t l = 0;
  size_t r = size;
  size_t p = 0;
  do {
    p = Partition(arr, l, r);
    if (p < k) {
      l = p + 1;
    } else {
      r = p;
    }
  } while (p != k);
}

// void Run(std::istream& in, std::ostream& out) {

// }

int main() {
  // Run(std::cin, std::cout);
  std::vector<int> arr = {1, 3, 5, 7, 2, 4, 6, 1, 2, 3};
  size_t k = 6;
  KthElement(&arr[0], arr.size(), k);
  std::cout << "kth element: " << arr[k] << "\n";
  return 0;
}