#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack : private std::vector<T> {
public:
    Stack() = default; // Utilize the vector's default constructor

    bool empty() const {
        return std::vector<T>::empty();
    }

    size_t size() const {
        return std::vector<T>::size();
    }

    void push(const T& item) {
        std::vector<T>::push_back(item);
    }

    void pop() {
        if (this->empty()) {
            throw std::underflow_error("Stack underflow");
        }
        std::vector<T>::pop_back();
    }

    const T& top() const {
        if (this->empty()) {
            throw std::underflow_error("Stack underflow");
        }
        return std::vector<T>::back();
    }
};

#endif 
