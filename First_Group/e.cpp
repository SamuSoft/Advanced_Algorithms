#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

vector<int> makeRandVec(int count){
  vector<int> retVal(count);
  int val = rand()%200;
  for (size_t i = 0; i < count; i++) {
    retVal[i] = val++;
  }
  return retVal;
}

bool findRightAnswer(const vector<int>& Bob, const vector<int>& Alice, const int len){
  int messageSize = 6;
  int ref;
  for (size_t i = 0; i < messageSize; i++) {
    ref = Bob[rand()%len];
    cout << ref << endl;
    if (std::find(Alice.begin(), Alice.end(), ref) != Alice.end()) {
      return true;
    }
  }
  return false;
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  vector<int> Bob = makeRandVec(100);
  vector<int> Alice = makeRandVec(100);
  int start = 0;
  int end = 0;
  if (Bob[0] > Alice[99] || Bob[99] < Alice[0]) {

  }else(){

  }

  cout << Bob[0] << " "  << Alice[0] << endl << findRightAnswer(Bob,Alice,100);

  return 0;
}
