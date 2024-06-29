#ifndef A2_SIMPLENAVIGATOR_SRC_STRUCTURES_S21_STACK_H
#define A2_SIMPLENAVIGATOR_SRC_STRUCTURES_S21_STACK_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T>
class stack {
 private:
  struct Node {
    T value;
    Node* next;

    Node(const T& value, Node* next = nullptr) : value(value), next(next) {}
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  size_type SizeOfStack;
  Node* head;

  void clean();

 public:
  stack();
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& s);
  stack(stack&& s) noexcept;
  ~stack();

  stack<value_type>& operator=(stack&& s) noexcept;
  stack<value_type>& operator=(const stack& s);

  const_reference top() const;

  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(stack& other) noexcept;

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  }
};

// ------------------
// РЕАЛИЗАЦИЯ ФУНКЦИЙ
// ------------------

template <typename T>
stack<T>::stack() : SizeOfStack(0), head(nullptr) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items)
    : SizeOfStack(0), head(nullptr) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename T>
stack<T>::stack(const stack& s) : SizeOfStack(0), head(nullptr) {
  Node* current = s.head;
  while (current != nullptr) {
    push(current->value);
    current = current->next;
  }
}

template <typename T>
stack<T>::stack(stack&& s) noexcept : SizeOfStack(s.SizeOfStack), head(s.head) {
  s.SizeOfStack = 0;
  s.head = nullptr;
}

template <typename T>
stack<T>::~stack() {
  clean();
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& other) noexcept {
  if (this != &other) {
    clean();
    SizeOfStack = other.SizeOfStack;
    head = other.head;
    other.SizeOfStack = 0;
    other.head = nullptr;
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& other) {
  if (this != &other) {
    clean();
    Node* current = other.head;
    while (current != nullptr) {
      push(current->value);
      current = current->next;
    }
  }
  return *this;
}

template <typename T>
void stack<T>::push(const_reference value) {
  head = new Node(value, head);
  ++SizeOfStack;
}

template <typename T>
void stack<T>::pop() {
  if (head != nullptr) {
    Node* temp = head;
    head = head->next;
    delete temp;
    --SizeOfStack;
  }
}

template <typename T>
void stack<T>::swap(stack<T>& other) noexcept {
  std::swap(head, other.head);
  std::swap(SizeOfStack, other.SizeOfStack);
}

template <typename T>
void stack<T>::clean() {
  while (head != nullptr) {
    pop();
  }
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (head != nullptr) {
    return head->value;
  }
  throw std::out_of_range("Stack is empty");
}

template <typename T>
bool stack<T>::empty() const {
  return SizeOfStack == 0;
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return SizeOfStack;
}

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_STRUCTURES_S21_STACK_H