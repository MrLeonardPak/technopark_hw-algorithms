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
#include <exception>
#include <iostream>
#include <limits>
#include <sstream>

template <typename T>
class DynamicArray {
 public:
  DynamicArray(size_t start_size) : size_(start_size), buffer_(new T[size_]) {}
  DynamicArray(size_t start_size, T const* buffer)
      : size_(start_size), buffer_(new T[size_]) {
    for (size_t i = 0; i < size_; ++i) {
      buffer_[i] = buffer[i];
    }
  }

  DynamicArray(DynamicArray const&) = delete;

  DynamicArray& operator=(DynamicArray const&) = delete;

  ~DynamicArray() {
    if (buffer_ != nullptr) {
      delete[] buffer_;
    }
  }

  T& operator[](int index) {
    if ((size_t)index >= size_) {
      throw std::out_of_range(
          "DynamicArray: [index] greater than size of buffer");
    }
    return buffer_[index];
  }

  void Increase(size_t const& current_use_size) {
    if (CheckForIncrease(current_use_size)) {
      Reallocation(size_ * kReallocMultiplication, current_use_size);
    }
  }
  void Decrease(size_t const& current_use_size) {
    if (CheckForIncrease(current_use_size)) {
      Reallocation(size_ / kReallocDivision, current_use_size);
    }
  }
  auto get_size() const { return size_; };

 private:
  const size_t kReallocMultiplication = 2;
  const size_t kReallocDivision = kReallocMultiplication * 2;

  size_t size_ = 0;
  T* buffer_ = nullptr;

  auto CheckForIncrease(size_t current_use_size) const {
    return current_use_size >= size_;
  }
  auto CheckForDecrease(size_t current_use_size) const {
    return size_ / current_use_size >= kReallocDivision;
  }
  void Reallocation(size_t const& new_max_size, size_t const& last_saved) {
    if (last_saved > new_max_size) {
      throw std::out_of_range(
          "Reallocation: last_saved greater than new_max_size");
    }

    T* new_buffer = new T[new_max_size];

    for (size_t i = 0; i < last_saved; ++i) {
      new_buffer[i] = buffer_[i];
    }
    size_ = new_max_size;

    delete[] buffer_;
    buffer_ = new_buffer;
  }
};

template <typename T>
struct DefaultComparator {
  bool operator()(T const& l, T const& r) const { return l > r; }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Heap {
 public:
  Heap(T const* buffer, size_t size, Comparator comp = Comparator())
      : heap_size_(size),
        buf_(new DynamicArray<T>(heap_size_, buffer)),
        comp_(comp) {
    BuildHeap();
  };

  Heap(Heap const&) = delete;

  Heap& operator=(Heap const&) = delete;

  ~Heap() { delete buf_; }

  void Push(T const& val) {
    buf_->Increase(heap_size_);

    ++heap_size_;
    (*buf_)[heap_size_ - 1] = val;
    SiftUp(heap_size_ - 1);
  };
  void Pop() {
    if (IsEmpty()) {
      throw std::out_of_range("Heap::Pop: empty heap");
    }

    (*buf_)[0] = (*buf_)[heap_size_ - 1];
    --heap_size_;

    if (IsEmpty()) {
      return;
    }
    SiftDown(0);
    buf_->Decrease(heap_size_);
  }

  T const& Top() const {
    if (IsEmpty()) {
      throw std::out_of_range("Heap::Top: empty heap");
    }
    return (*buf_)[0];
  };
  bool IsEmpty() const { return heap_size_ == 0; }

 private:
  size_t heap_size_;
  DynamicArray<T>* buf_;
  Comparator comp_;

  void SiftDown(size_t from_index) {
    size_t left = 2 * from_index + 1;
    size_t right = 2 * from_index + 2;
    size_t target = from_index;
    if (left < heap_size_ && comp_((*buf_)[left], (*buf_)[target])) {
      target = left;
    }
    if (right < heap_size_ && comp_((*buf_)[right], (*buf_)[target])) {
      target = right;
    }
    if (target != from_index) {
      std::swap((*buf_)[from_index], (*buf_)[target]);
      SiftDown(target);
    }
  }
  void SiftUp(size_t from_index) {
    while (from_index > 0) {
      size_t parent = (from_index - 1) / 2;
      if (comp_((*buf_)[parent], (*buf_)[from_index])) {
        return;
      }
      std::swap((*buf_)[from_index], (*buf_)[parent]);
      from_index = parent;
    }
  }
  void BuildHeap() {
    // size_t после декримировании ниже нуля выдаст максимальное значение
    for (size_t i = heap_size_ / 2 - 1; i != std::numeric_limits<size_t>::max();
         --i) {
      SiftDown(i);
    }
  }
};

struct Process {
  int P = 0;
  int T = 0;
  int t = 0;
  int Value() const { return P * (t + 1); }
};

template <typename Comporator>
size_t ExecuteTasks(Heap<Process, Comporator>* heap) {
  size_t switchings = 0;
  while (!heap->IsEmpty()) {
    switchings++;
    Process top = heap->Top();
    heap->Pop();
    top.t += top.P;
    if (top.t < top.T) {
      heap->Push(top);
    }
  }
  return switchings;
}

void TestDynamicArray() {
  {
    DynamicArray<int> arr(1);
    arr[0] = 1;
    try {
      arr[1] = 1;
      assert(false);
    } catch (std::out_of_range const& e) {
    }
  }
  {
    DynamicArray<size_t> arr(16);
    for (size_t i = 0; i < 16; ++i) {
      arr[i] = i;
    }
    arr.Increase(16);
    for (size_t i = 16; i < 32; ++i) {
      arr[i] = i;
    }
    for (size_t i = 0; i < 16; ++i) {
      assert(arr[i] == i);
    }
    for (size_t i = 16; i < 32; ++i) {
      assert(arr[i] == i);
    }
  }
  {
    DynamicArray<size_t> arr(16);
    for (size_t i = 0; i < 4; ++i) {
      arr[i] = i;
    }
    arr.Decrease(4);
    for (size_t i = 0; i < 4; ++i) {
      assert(arr[i] == i);
    }
  }
  std::cout << "TestDynamicArray: SUCCESS!"
            << "\n";
}

void TestHeap() {
  {
    int arr[] = {1};
    Heap<int> h(arr, 1);
    assert(!h.IsEmpty());

    h.Push(2);
    assert(h.Top() == 2);
    h.Pop();
    h.Pop();
    assert(h.IsEmpty());

    for (int i = 0; i < 10; ++i) {
      h.Push(i);
    }
    for (int i = 9; i >= 0; --i) {
      assert(h.Top() == i);
      h.Pop();
    }
    assert(h.IsEmpty());

    std::cout << "TestHeap: SUCCESS" << std::endl;
  }
}

void Run(std::istream& in, std::ostream& out) {
  size_t process_size = 0;
  in >> process_size;
  auto process_arr = new Process[process_size];
  for (size_t i = 0; i < process_size; ++i) {
    int tmp_P = 0;
    int tmp_T = 0;
    in >> tmp_P >> tmp_T;
    process_arr[i] = {tmp_P, tmp_T, 0};
  }

  Heap heap(process_arr, process_size, [](Process const& l, Process const& r) {
    return l.Value() < r.Value();
  });

  out << ExecuteTasks(&heap);
  delete[] process_arr;
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 1 10 1 5 2 5" << std::endl;
    Run(in, out);
    assert(out.str() == "18");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  // TestDynamicArray();
  // TestHeap();
  // TestContest();
  Run(std::cin, std::cout);
  return 0;
}