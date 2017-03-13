#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

void store_file(string);
bool two_sum(int);
long get_count(void);

unordered_set<long> hash_table;
const int LEFT = -10000;
const int RIGHT = 10000;

int main(int argc, char** argv) {

  store_file("/Users/alex.paniutin/Documents/Study/GitHub/Miscellaneous/TwoSum20k/2sum.txt");

  long cnt = get_count();

  cout << cnt << endl;

  return 0;
}

void store_file(string filename) {
  ifstream infile;
  infile.open(filename, ios::in);
  long tmp;
  while (infile >> tmp) {
    hash_table.insert(tmp);
  }
  cout << "FINISH!" << endl;
  infile.close();
}

bool two_sum(int target) {
  for (auto it = hash_table.begin(); it != hash_table.end(); ++it) {
    long tmp = target - *it;;
    auto res = hash_table.find(tmp);
    if (res != hash_table.end() and res != it)
      return true;
  }
  return false;
}

long get_count(void) {
  int cnt = 0;
  for (int i = LEFT; i <= RIGHT; ++i) {
    if (two_sum(i))
      ++cnt;
    if (! (i%100))
      cout << "check: " << i << endl;
  }
  return cnt;
}