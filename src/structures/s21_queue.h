#ifndef A2_SIMPLENAVIGATOR_SRC_STRUCTURES_S21_QUEUE_H
#define A2_SIMPLENAVIGATOR_SRC_STRUCTURES_S21_QUEUE_H

#include <stdexcept>

namespace s21 {

template <typename T>
class queue {
  struct Node {
    T value;
    Node* next;

    Node(const T& val) : value(val), next(nullptr) {}
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  size_type SizeOfQueue;
  Node* first;
  Node* last;

  void clean();

 public:
  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& q);
  queue(queue&& q);
  ~queue();

  queue<value_type>& operator=(queue&& q);

  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(queue& other);

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  }
};

// ------------------
// РЕАЛИЗАЦИЯ ФУНКЦИЙ
// ------------------

template <typename T>
queue<T>::queue() : SizeOfQueue(0), first(nullptr), last(nullptr) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const& items)
    : SizeOfQueue(0), first(nullptr), last(nullptr) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename T>
queue<T>::queue(const queue& q)
    : SizeOfQueue(0), first(nullptr), last(nullptr) {
  Node* current = q.first;
  while (current != nullptr) {
    push(current->value);
    current = current->next;
  }
}

template <typename T>
queue<T>::queue(queue&& q)
    : SizeOfQueue(q.SizeOfQueue), first(q.first), last(q.last) {
  q.SizeOfQueue = 0;
  q.first = nullptr;
  q.last = nullptr;
}

template <typename T>
queue<T>::~queue() {
  clean();
}

template <typename T>
queue<T>& queue<T>::operator=(queue<T>&& other) {
  if (this != &other) {
    clean();
    SizeOfQueue = other.SizeOfQueue;
    first = other.first;
    last = other.last;
    other.SizeOfQueue = 0;
    other.first = nullptr;
    other.last = nullptr;
  }
  return *this;
}

template <typename T>
void queue<T>::push(const_reference value) {
  Node* newNode = new Node(value);
  if (size() == 0) {
    first = last = newNode;
  } else {
    last->next = newNode;
    last = newNode;
  }
  SizeOfQueue++;
}

template <typename T>
void queue<T>::pop() {
  if (size() == 1) {
    delete last;
    first = nullptr;
    last = nullptr;
    SizeOfQueue--;
  } else if (size() > 1 && last != nullptr) {
    Node* temp = first;
    first = first->next;
    delete temp;
    SizeOfQueue--;
  }
}

template <typename T>
void queue<T>::swap(queue<T>& other) {
  Node* tempLast = last;
  last = other.last;
  other.last = tempLast;

  Node* tempFirst = first;
  first = other.first;
  other.first = tempFirst;

  size_type tempSize = SizeOfQueue;
  SizeOfQueue = other.SizeOfQueue;
  other.SizeOfQueue = tempSize;
}

template <typename T>
void queue<T>::clean() {
  while (SizeOfQueue) {
    pop();
  }
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (last != nullptr) {
    return last->value;
  }
  throw std::out_of_range("queue is empty");
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (first != nullptr) {
    return first->value;
  }
  throw std::out_of_range("queue is empty");
}

template <typename T>
bool queue<T>::empty() const {
  return SizeOfQueue == 0;
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return SizeOfQueue;
}

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_STRUCTURES_S21_QUEUE_H
