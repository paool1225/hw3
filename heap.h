#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>


template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:

  Heap(int m=2, PComparator c = PComparator());
  ~Heap();
  void push(const T& item);
  T const & top() const;
  void pop();
  bool empty() const;
  int size() const;

private:
  void heapify(size_t index);
  PComparator comp;
  int k_ary;
  std::vector<T> h;

};
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return h.size()==0;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  comp = c;
  if(m < 2){
    throw std::logic_error("can't have value under 2");
  }
  k_ary = m;

}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){
  
}

template <typename T, typename PComparator>
int Heap<T,PComparator>::size() const{
  return h.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t index){
  size_t leafid; 
  size_t pri = k_ary*index + 1; 

  if(k_ary*index + 1 > h.size()-1){
    return;
  }
  else{
    for(int i = 2; i <= k_ary; i++){
      leafid = k_ary*index + i;
      if(leafid < h.size()){
        if(comp(h[leafid], h[pri])){
          pri = leafid;
        }
      }
    }
    if(comp(h[pri], h[index])){
      std::swap(h[pri], h[index]);
      heapify(pri);
    }
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
    h.push_back(item);
    int loc = h.size()-1;
    int parent = (loc-1)/k_ary;
    while(loc >= 0 && comp(h[loc], h[parent])){ 
        std::swap(h[parent], h[loc]);
        loc = parent;
        parent = (loc-1)/k_ary;
    }
}
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  
  if(empty()){
    
    throw std::underflow_error("Heap is empty");
  }
 
  return h[0]; 

}
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    
    throw std::underflow_error("Heap is empty");

  }
  if(h.size() == 1){
    h.pop_back();
    return;
  }
  std::swap(h[0], h[h.size()-1]);
  h.pop_back();
  heapify(0);
}
#endif