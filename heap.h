#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <functional>
#include <stdexcept>

template <typename T, typename PComparator = std::less<T> >
class Heap {
public:
    Heap(int m=2, PComparator c = PComparator()) : ary(m), comp(c) {}

    void push(const T& item) {
        elems.push_back(item);
        heapifyUp(elems.size() - 1);
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Heap is empty");
        }
        std::swap(elems[0], elems.back());
        elems.pop_back();
        heapifyDown(0);
    }

    T const & top() const {
        if (empty()) {
            throw std::underflow_error("Heap is empty");
        }
        return elems.front();
    }

    bool empty() const {
        return elems.empty();
    }

    size_t size() const {
        return elems.size();
    }

private:
    std::vector<T> elems; 
    int ary; 
    PComparator comp; 

    void heapifyUp(size_t idx) {
        while (idx > 0) {
            size_t parentIdx = (idx - 1) / ary;
            if (comp(elems[idx], elems[parentIdx])) {
                std::swap(elems[idx], elems[parentIdx]);
                idx = parentIdx;
            } else {
                break;
            }
        }
    }

    void heapifyDown(size_t idx) {
        size_t childIdx = ary * idx + 1; 
        while (childIdx < elems.size()) {
            size_t minMaxIdx = idx;
            for (int i = 0; i < ary && i + childIdx < elems.size(); ++i) {
                if (comp(elems[childIdx + i], elems[minMaxIdx])) {
                    minMaxIdx = childIdx + i;
                }
            }
            if (minMaxIdx != idx) {
                std::swap(elems[idx], elems[minMaxIdx]);
                idx = minMaxIdx;
                childIdx = ary * idx + 1;
            } else {
                break;
            }
        }
    }
};

#endif 
