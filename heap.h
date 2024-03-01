#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T>>
class Heap
{
public:
    Heap(int m=2, PComparator c = PComparator());
    ~Heap() = default; // Use default destructor
    void push(const T& item);
    T const & top() const;
    void pop();
    bool empty() const;
    int size() const;

private:
    std::vector<T> data;
    PComparator comp;
    int m; // Arity of the heap

    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
};

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : comp(c), m(m) {
    if (m < 2) {
        throw std::invalid_argument("Heap arity must be at least 2");
    }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
    data.push_back(item);
    heapifyUp(data.size() - 1);
}

template <typename T, typename PComparator>
T const & Heap<T, PComparator>::top() const {
    if (empty()) {
        throw std::underflow_error("Heap is empty");
    }
    return data.front();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::pop() {
    if (empty()) {
        throw std::underflow_error("Heap is empty");
    }
    std::swap(data.front(), data.back());
    data.pop_back();
    if (!empty()) {
        heapifyDown(0);
    }
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
    return data.empty();
}

template <typename T, typename PComparator>
int Heap<T, PComparator>::size() const {
    return data.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / m;
        if (comp(data[index], data[parent])) {
            std::swap(data[index], data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyDown(size_t index) {
    size_t child = m * index + 1; // First child
    while (child < data.size()) {
        size_t minChild = child;
        for (int i = 1; i < m; ++i) { // Find smallest child
            size_t nextChild = m * index + 1 + i;
            if (nextChild < data.size() && comp(data[nextChild], data[minChild])) {
                minChild = nextChild;
            }
        }
        if (comp(data[minChild], data[index])) {
            std::swap(data[index], data[minChild]);
            index = minChild;
            child = m * index + 1;
        } else {
            break;
        }
    }
}

#endif 