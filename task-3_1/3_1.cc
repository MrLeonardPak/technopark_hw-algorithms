#include <cassert>
#include <iostream>
#include <sstream>

void TestQueue();
void TestContest();
void Run(std::istream& in, std::ostream& out);

class Queue {
 public:
  Queue() : head(nullptr), tail(nullptr) {}
  ~Queue();
  Queue(Queue const&) = delete;  // Конструктор Копирование
  Queue& operator=(Queue const&) = delete;  // Присваивание

  void PushBack(int const& val);
  int PopFront();

  bool IsEmpty() const { return head == tail && head == nullptr; }

 private:
  struct Node {
    Node* next;
    int val;

    Node(int const& val) : next(nullptr), val(val) {}
  };

  Node* head;
  Node* tail;
};

Queue::~Queue() {
  while (head != nullptr) {
    Node* node = head;
    head = head->next;
    delete node;
  }
}

int Queue::PopFront() {
  assert(!IsEmpty());

  Node* node = head;
  int val = node->val;
  head = head->next;
  delete node;

  if (head == nullptr) {
    tail = nullptr;
  }
  return val;
}

void Queue::PushBack(int const& val) {
  Node* node = new Node(val);
  if (IsEmpty()) {
    head = tail = node;
  } else {
    tail->next = node;
    tail = node;
  }
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