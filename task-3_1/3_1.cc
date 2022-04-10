#include <cassert>
#include <iostream>
#include <sstream>

class CycleDynamicBuffer {
 public:
  CycleDynamicBuffer(size_t start_size);
  ~CycleDynamicBuffer();

  CycleDynamicBuffer(CycleDynamicBuffer const&) = delete;
  CycleDynamicBuffer& operator=(CycleDynamicBuffer const&) = delete;

  void PushBack(int const& val);
  int PopFront();
  bool IsEmpty() const { return size_ == 0; }

 private:
  size_t kStartSize = 1;
  int kReallocMultiplication = 2;

  size_t head_index_ = 0;
  size_t tail_index_ = 0;
  size_t size_ = 0;
  size_t max_size_ = 0;
  int* dynamic_array_ = nullptr;

  void Reallocation(size_t const& new_max_size);
  size_t ShiftIndex(size_t const& index, unsigned int shift);
};

CycleDynamicBuffer::CycleDynamicBuffer(size_t start_size)
    : kStartSize(start_size),
      size_(0),
      max_size_(kStartSize),
      dynamic_array_(new int[max_size_]) {}

CycleDynamicBuffer::~CycleDynamicBuffer() {
  if (dynamic_array_ != nullptr) {
    delete[] dynamic_array_;
  }
}

void CycleDynamicBuffer::PushBack(int const& val) {
  // Для пустого буффера не сдвигаем tail_index_
  if (IsEmpty()) {
    ++size_;
    dynamic_array_[tail_index_] = val;
  } else {
    if (size_ == max_size_) {
      Reallocation(max_size_ * kReallocMultiplication);
    }
    ++size_;
    tail_index_ = ShiftIndex(tail_index_, 1);
    dynamic_array_[tail_index_] = val;
  }
}

int CycleDynamicBuffer::PopFront() {
  assert(!IsEmpty());
  int val = dynamic_array_[head_index_];
  --size_;
  if (IsEmpty()) {
    return val;
  }
  head_index_ = ShiftIndex(head_index_, 1);
  // Уменьшаем динамический массив только в том случае, если действующие
  // элементы занимают меньше, чем половину от уменьшенного массива
  if ((int)(max_size_ / size_) >= kReallocMultiplication * 2) {
    Reallocation(max_size_ / kReallocMultiplication);
  }

  return val;
}

void CycleDynamicBuffer::Reallocation(size_t const& new_max_size) {
  int* new_array = new int[new_max_size];
  //  Заносим децствующие элементы в начало нового массива по порядку от head_
  //  до tail_
  for (size_t i = 0; i < size_; ++i) {
    new_array[i] = dynamic_array_[ShiftIndex(head_index_, i)];
  }
  max_size_ = new_max_size;
  head_index_ = 0;
  tail_index_ = size_ - 1;

  delete[] dynamic_array_;
  dynamic_array_ = new_array;
}

size_t CycleDynamicBuffer::ShiftIndex(size_t const& index, unsigned int shift) {
  // index сдвигается вперед на shift, значение index зациклено и ограничего
  // значением max_size_
  return (index + shift) % max_size_;
}

void Run(std::istream& in, std::ostream& out) {
  int n = 0;
  CycleDynamicBuffer q(1);
  in >> n;
  bool result = true;
  for (int i = 0; i < n; ++i) {
    int a = 0;
    int b = 0;
    in >> a >> b;
    switch (a) {
      case 2:
        if (!q.IsEmpty()) {
          result &= (q.PopFront() == b) ? true : false;
        } else {
          result &= (-1 == b) ? true : false;
        }
        break;
      case 3:
        q.PushBack(b);
        break;
      default:
        assert(false);
    }
  }
  out << (result ? "YES" : "NO") << std::endl;
}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "3 3 44 3 50 2 44" << std::endl;
    Run(in, out);
    assert(out.str() == "YES\n");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "2 2 -1 3 10" << std::endl;
    Run(in, out);
    assert(out.str() == "YES\n");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "2 3 44 2 66" << std::endl;
    Run(in, out);
    assert(out.str() == "NO\n");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "1000000" << std::endl;
    for (size_t i = 0; i < 500000; ++i) {
      in << "3 " << i << std::endl;
    }
    for (size_t i = 0; i < 500000; ++i) {
      in << "2 " << i << std::endl;
    }

    Run(in, out);
    assert(out.str() == "YES\n");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "800" << std::endl;
    for (size_t i = 0; i < 200; ++i) {
      in << "3 " << i << std::endl;
    }
    for (size_t i = 0; i < 100; ++i) {
      in << "2 " << i << std::endl;
    }
    for (size_t i = 0; i < 200; ++i) {
      in << "3 " << i << std::endl;
    }
    for (size_t i = 100; i < 200; ++i) {
      in << "2 " << i << std::endl;
    }
    for (size_t i = 0; i < 200; ++i) {
      in << "2 " << i << std::endl;
    }

    Run(in, out);
    assert(out.str() == "YES\n");
  }
  {
    std::stringstream in;
    std::stringstream out;
    in << "800" << std::endl;
    for (size_t i = 0; i < 200; ++i) {
      in << "3 " << i << std::endl;
    }
    for (size_t i = 0; i < 100; ++i) {
      in << "2 " << i << std::endl;
    }
    for (size_t i = 0; i < 200; ++i) {
      in << "3 " << i << std::endl;
    }
    for (size_t i = 100; i < 200; ++i) {
      in << "2 " << i << std::endl;
    }
    for (size_t i = 0; i < 200; ++i) {
      in << "2 " << i << std::endl;
    }
    in << "2 -1" << std::endl;
    Run(in, out);
    assert(out.str() == "YES\n");
  }

  std::cout << "TestLogic: SUCCESS" << std::endl;
}

void TestQueue() {
  CycleDynamicBuffer q(1);
  assert(q.IsEmpty());

  q.PushBack(1);
  assert(q.PopFront() == 1);
  assert(q.IsEmpty());

  for (int i = 0; i < 100; ++i) {
    q.PushBack(i);
  }
  for (int i = 0; i < 100; ++i) {
    assert(q.PopFront() == i);
  }
  assert(q.IsEmpty());

  std::cout << "TestQueue: SUCCESS" << std::endl;
}

int main() {
  TestQueue();
  TestContest();
  // Run(std::cin, std::cout);
  return 0;
}