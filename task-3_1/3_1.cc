#include <cassert>
#include <iostream>
#include <sstream>

void TestQueue();
void TestContest();
void Run(std::istream& in, std::ostream& out);

class CycleDynamicBuffer {
 public:
  CycleDynamicBuffer() {}
  ~CycleDynamicBuffer();

  CycleDynamicBuffer(CycleDynamicBuffer const&) = delete;
  CycleDynamicBuffer& operator=(CycleDynamicBuffer const&) = delete;

  void AddItem(int const& val);
  int RemoveItem();
  bool IsEmpty() const { return size_ == 0; }

 private:
  int* dynamic_array_ = nullptr;
  size_t head_index_ = 0;
  size_t tail_index_ = 0;
  size_t size_ = 0;
  size_t max_size_ = 0;

  void Reallocation(size_t const& new_max_size);
  size_t ShiftIndex(size_t const& index, unsigned int shift) {
    return (index + shift) % max_size_;
  }
};

CycleDynamicBuffer::~CycleDynamicBuffer() {
  if (dynamic_array_ != nullptr) {
    delete[] dynamic_array_;
  }
}

void CycleDynamicBuffer::AddItem(int const& val) {
  if (IsEmpty()) {
    size_ = 1;
    max_size_ = 1;
    dynamic_array_ = new int[max_size_];
    dynamic_array_[0] = val;
  } else {
    if (size_ == max_size_) {
      Reallocation(max_size_ * 2);
    }
    ++size_;
    tail_index_ = ShiftIndex(tail_index_, 1);
    dynamic_array_[tail_index_] = val;
  }
}

int CycleDynamicBuffer::RemoveItem() {
  assert(!IsEmpty());
  int val = dynamic_array_[head_index_];
  if (--size_ == 0) {
    return val;
  }
  head_index_ = ShiftIndex(head_index_, 1);

  if (max_size_ / size_ >= 4) {
    Reallocation(max_size_ / 2);
  }

  return val;
}

void CycleDynamicBuffer::Reallocation(size_t const& new_max_size) {
  int* new_array = new int[new_max_size];
  //  Выравниваем в новом массиве в начало от головы до хвоста
  for (size_t i = 0; i < size_; ++i) {
    // Сдвигаемся по изновальному массиву от головы (head_index_) на количество
    // действительных элементов (size_), ограничивая индекс по size_
    new_array[i] = dynamic_array_[ShiftIndex(head_index_, i)];
  }
  max_size_ = new_max_size;
  head_index_ = 0;
  tail_index_ = size_ - 1;

  delete[] dynamic_array_;
  dynamic_array_ = new_array;
}

class Queue {
 public:
  Queue() : buffer(new CycleDynamicBuffer()) {}
  ~Queue();
  Queue(Queue const&) = delete;  // Конструктор Копирование
  Queue& operator=(Queue const&) = delete;  // Присваивание

  void PushBack(int const& val);
  int PopFront();

  bool IsEmpty() const { return buffer->IsEmpty(); }

 private:
  CycleDynamicBuffer* buffer;
};

Queue::~Queue() {
  if (buffer != nullptr) {
    delete buffer;
  }
}

int Queue::PopFront() {
  assert(!IsEmpty());
  return buffer->RemoveItem();
}

void Queue::PushBack(int const& val) {
  buffer->AddItem(val);
}

int main() {
  TestQueue();
  TestContest();
  // Run(std::cin, std::cout);
  return 0;
}

void Run(std::istream& in, std::ostream& out) {
  int n = 0;
  Queue q;
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

  std::cout << "TestLogic: SUCCESS" << std::endl;
}

void TestQueue() {
  Queue q;
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