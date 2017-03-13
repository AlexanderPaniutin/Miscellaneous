#include <iostream>
#include <fstream>
#include "max_heap.h"
#include "min_heap.h"
using namespace std;

void addIntoHeaps(MaxHeap<int> &maxHeap, MinHeap<int> &minHeap, int number);
void balanceHeaps(MaxHeap<int> &maxHeap, MinHeap<int> &minHeap);
int getMedian(MaxHeap<int> &maxHeap, MinHeap<int> &minHeap);

int main() {

  // READ the file
  fstream fstrm;
  fstrm.open("/Users/alex.paniutin/Documents/Study/GitHub/Miscellaneous/MedianByHeaps/median.txt", ios::in);
  if (fstrm.is_open() == false) {
    cout << "failed to open a file" << endl;
    return -1;
  }

  // define max and min heaps
  MaxHeap<int> maxHeap;
  MinHeap<int> minHeap;

  int currNumber;
  int sumMod10k = 0;
  while (fstrm.eof() == false) {
    fstrm >> currNumber;
    addIntoHeaps(maxHeap, minHeap, currNumber);
    cout << currNumber << '\t' << getMedian(maxHeap, minHeap);
    if (maxHeap.size() > 10)
      cout << endl;
    else
      cout << '\t' << maxHeap.trace() << '\t' << minHeap.trace() << endl;
    sumMod10k += getMedian(maxHeap, minHeap);
    if (sumMod10k >= 10000) {
      sumMod10k -= 10000;
    }
  }
  fstrm.close();

  cout << "result: " << sumMod10k << endl;
//  for (int i=1; i<=5; i++) {
//    addIntoHeaps(maxHeap, minHeap, i);
//    cout << "add:  " << i << endl;
//    cout << "heaps [" << maxHeap.trace() << " | " << minHeap.trace() << "]" << endl;
//    cout << "med:  " << getMedian(maxHeap, minHeap) << endl << endl;
//  }

  return 0;
}

void addIntoHeaps(MaxHeap<int> &maxHeap, MinHeap<int> &minHeap, int number) {
  // insert into the first part if less then median
  if (number < getMedian(maxHeap, minHeap)) {
    maxHeap.add(number);
  } else {
    minHeap.add(number);
  }

  balanceHeaps(maxHeap, minHeap);
}

void balanceHeaps(MaxHeap<int> &maxHeap, MinHeap<int> &minHeap) {
  // we need to make sure that maxHeap is bigger than minHeap no more than 1
  while (true) {
    int diffSize = maxHeap.size() - minHeap.size();

    if (diffSize == 0 || diffSize == 1) {
      break;
    }

    // maxHeap is bigger than minHeap
    if (diffSize > 0) {
      minHeap.add(maxHeap.popMax());
    } else {
      maxHeap.add(minHeap.popMin());
    }
  }
}

int getMedian(MaxHeap<int> &maxHeap, MinHeap<int> &minHeap) {
  // we need to assume that heaps are balanced at this moment
  if (maxHeap.size() >= minHeap.size()) {
    return maxHeap.getMax();
  } else {
    return minHeap.getMin();
  }
}