#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>

using namespace std;

typedef chrono::high_resolution_clock::time_point timep;
timep time_now()
{
  return std::chrono::high_resolution_clock::now();
}

long long int time_diff_ms(timep p1, timep p2)
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(p1 - p2).count();
}

bool readSet(unordered_set<long> &inputSet);

int main() {
  unordered_set<long> inputSet;
  readSet(inputSet);

  fstream fstrm;
  fstrm.open("/Users/alex.paniutin/Documents/Study/GitHub/Miscellaneous/TwoSum20k/2sum_out.txt", ios::out);

  int ndx = 0;
  long totalPairs = 0;
  unordered_set<long>::iterator it = inputSet.begin();
  while (it != inputSet.end()) {
    long currItem = *it;
    for (long target=-10000; target<=10000; target++) {
      long pairItem = target - currItem;
      if (inputSet.find(pairItem) != inputSet.end()) {
        //cout << ndx << " found pair " << currItem << '+' << pairItem << '=' << target << endl;
        totalPairs++;
        fstrm << currItem << ';' << pairItem << endl;
      }
    }
    it++;
    ndx++;
    if (ndx%1000 == 0) cout << ndx << " found " << totalPairs << endl;
  }

  fstrm.close();
  cout << "total pairs found: " << totalPairs << endl;

}

bool readSet(unordered_set<long> &inputSet) {
  fstream fstrm;
  fstrm.open("/Users/alex.paniutin/Documents/Study/GitHub/Miscellaneous/TwoSum20k/2sum.txt", ios::in);
  if (fstrm.is_open() == false) {
    cout << "failed to open a file" << endl;
    return false;
  }

  long currNumber = 0;
  while (fstrm.eof() == false) {
    fstrm >> currNumber;
    inputSet.insert(currNumber);
  }
  fstrm.close();

  return true;
}