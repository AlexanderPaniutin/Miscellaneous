#ifndef MIN_HEAP_H_
#error Please inlcude .h instead of .tcc
#endif

#include <sstream>

template<class T>
MinHeap<T>::MinHeap() {
  // use 0-at-the-beginnig style
  data.push_back(T());
}

template<class T>
void MinHeap<T>::add(const T &item) {
  // add in the end
  data.push_back(item);
  unsigned int ndx = data.size() - 1;
  unsigned int parentNdx = ndx / 2;
  while (parentNdx != 0) {
    if (data[parentNdx] < data[ndx])
      break;
    else {
      //swap
      T tmp = data[parentNdx];
      data[parentNdx] = data[ndx];
      data[ndx] = tmp;
    }

    ndx = parentNdx;
    parentNdx = parentNdx / 2;
  }
}

template<class T>
T MinHeap<T>::getMin(void) {
  if (data.size() <= 0)
    return T();
  else
    return data[1];
}

template<class T>
T MinHeap<T>::popMin(void) {
  // 0 ndx is an internal data
  if (data.size() <= 1)
    return T();

  T topItem = data[1];
  // put the last item into the front and pop last
  data[1] = data[data.size() - 1];
  data.pop_back();

  // now correct the validity
  unsigned int ndxParent = 1;
  unsigned int ndxChild1 = ndxParent * 2;
  unsigned int ndxChild2 = ndxParent * 2 + 1;
  while (ndxParent < data.size()) {
    // this is the index of a next child. TBD below
    unsigned int ndxMax = ndxParent;

    // if both children are available
    if (ndxChild1 < data.size() && ndxChild2 < data.size()) {
      ndxMax = ndxChild1;
      if (data[ndxChild2] < data[ndxChild1])
        ndxMax = ndxChild2;
    }
    else if (ndxChild1 < data.size()) {
      ndxMax = ndxChild1;
    }
    else if (ndxChild2 < data.size()) {
      ndxMax = ndxChild2;
    }
    else {
      // here, none of the children are in valid range so balancing is done
      break;
    }

    // check if we still need to proceed
    if (data[ndxParent] <= data[ndxMax])
      break;

    // swap parent and ndxMax
    T tmp = data[ndxMax];
    data[ndxMax] = data[ndxParent];
    data[ndxParent] = tmp;

    // update ndxParent and children
    ndxParent = ndxMax;
    ndxChild1 = ndxParent * 2;
    ndxChild2 = ndxParent * 2 + 1;
  }
  return topItem;
}

template<class T>
std::string MinHeap<T>::trace(void) {
  if (data.size() < 1)
    return "";

  std::stringstream strm;
  bool isFirst = true;

  for (unsigned int i = 1; i < data.size(); ++i) {
    if (isFirst)
      isFirst = false;
    else
      strm << ',';
    strm << data[i];
  }

  return strm.str();
}

template<class T>
bool MinHeap<T>::isValid() {
  // go from end to the beginning and verify child vs parent.
  unsigned int ndxChild = data.size() - 1;
  unsigned int ndxParent = ndxChild / 2;
  bool isValid = true;

  while (ndxParent > 0) {
    if (data[ndxChild] < data[ndxParent]) {
      isValid = false;
      break;
    }

    ndxChild -= 1;
    ndxParent = ndxChild / 2;
  }

  return isValid;
}

template<class T>
size_t MinHeap<T>::size() {
  return data.size();
}