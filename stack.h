#ifndef STACK_H
#define STACK_H
#include <vector>
#include <stdexcept>

template <typename T>
class Stack : private std::vector<T> {
public:
    Stack(); 
    // The destructor is unnecessary to define explicitly if it does nothing.
    // The default destructor provided by the compiler is sufficient since
    // std::vector's destructor will be called automatically to clean up.
    bool empty() const; 
    size_t size() const; 
    void push(const T& item); 
    void pop(); 
    const T& top() const; 
};

template <typename T>
Stack<T>::Stack() : std::vector<T>() {
    // Constructor initializes the vector part of the stack.
}

template <typename T>
bool Stack<T>::empty() const {
    return std::vector<T>::empty(); 
}

template <typename T>
size_t Stack<T>::size() const {
    return std::vector<T>::size(); 
}

template <typename T>
void Stack<T>::push(const T& item) {
    std::vector<T>::push_back(item); 
}

template <typename T>
void Stack<T>::pop() {
    if (this->empty()) { 
        throw std::underflow_error("Stack is empty");
    }
    std::vector<T>::pop_back(); 
}

template <typename T>
const T& Stack<T>::top() const {
    if (this->empty()) { 
        throw std::underflow_error("Stack is empty");
    }
    return std::vector<T>::back(); 
}

#endif 
