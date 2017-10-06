#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

vector<int> makeRandVec(int count){
  vector<int> retVal(count);
  int val = rand()%100;
  for (size_t i = 0; i < count; i++) {
    retVal[i] = val++;
  }
  return retVal;
}



int main(int argc, char const *argv[]) {
  srand(time(NULL));
  vector<int> Bob = makeRandVec(100);
  vector<int> Alice = makeRandVec(100);
  cout << Bob[0] << " "  << Alice[0] << endl;
  return 0;
}
