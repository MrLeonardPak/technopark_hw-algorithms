#include <assert.h>
#include <iostream>

class Queue {
 public:
  Queue() : head(nullptr), tail(nullptr) {}
  ~Queue() {
    while (!Empty()) {
      PopFront();
    }
  }
  Queue(Queue const&) = delete;             // Копирование
  Queue& operator=(Queue const&) = delete;  // Присваивание

  void PushBack(int val) {
    Node* node = new Node(val);
    if (Empty()) {
      head = tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }
  int PopFront() {
    Node* node = head;
    int val = node->val;

    head = head->next;
    delete node;

    if (head == nullptr) {
      tail = nullptr;
    }
    return val;
  }

  bool Empty() const { return head == tail && head == nullptr; }

 private:
  struct Node {
    Node* next;
    int val;

    Node(int val) : next(nullptr), val(val) {}
  };

  Node* head;
  Node* tail;
};

void TestQueue() {
  Queue q;
  assert(q.Empty());

  q.PushBack(1);
  assert(q.PopFront() == 1);
  assert(q.Empty());

  for (int i = 0; i < 100; ++i) {
    q.PushBack(i);
  }
  for (int i = 0; i < 100; ++i) {
    assert(q.PopFront() == i);
  }
  assert(q.Empty());
}

int main() {
  TestQueue();
  std::cout << "OK" << std::endl;
  return 0;
}