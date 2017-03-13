#ifndef MAX_HEAP_H_
#define MAX_HEAP_H_

/**
 * The HEAP implementation
 */

#include <vector>
#include <string>

template<class T>
class MaxHeap {
 public:
  MaxHeap();
  void add(const T &item);
  T getMax(void);
  T popMax(void);
  std::string trace(void);
  bool isValid(void);
  size_t size(void);

 private:
  std::vector<T> data;
};

#include "max_heap.tcc"

#endif // MAX_HEAP_H_
