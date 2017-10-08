#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>


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
    //cout << ref << endl;
    if (std::find(Alice.begin(), Alice.end(), ref) != Alice.end()) {
      return true;
    }
  }
  return false;
}

bool alwaysRightAnswer(const vector<int>& Bob, const vector<int>& Alice, const int len){
  int BobIndex = 0;
  int AliceIndex = 0;
  int matches = 0;
  while (BobIndex < len && AliceIndex < len) {
    if(Bob[BobIndex] > Alice[AliceIndex]){
      AliceIndex = AliceIndex+1;
    }else if(Bob[BobIndex] == Alice[AliceIndex]){
      BobIndex = BobIndex+1;
      AliceIndex = AliceIndex+1;
      matches = matches + 1;
    }else{
      BobIndex = BobIndex+1;
    }
  }
  if(len/10 <= matches)
    return true;
  return false;

}

bool testAlgorithm(const int len){
  vector<int> Bob = makeRandVec(len);
  vector<int> Alice = makeRandVec(len);
  bool ourAlg = findRightAnswer(Bob,Alice,len);
  bool ans = alwaysRightAnswer(Bob,Alice,len);
  cout << Bob[0] << endl << Alice[0] << endl;
  cout << ourAlg << endl << ans << endl;
  if(ourAlg != ans && !ans){
    throw invalid_argument("Breaking established rules for this excercise: Yes when no elements are the same");
  }else if(ourAlg == ans){
    return true;
  }else{
    return false;
  }
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  cout << testAlgorithm(100) << endl;

  // cout << Bob[0] << " "  << Alice[0] << endl;
  // if(alwaysRightAnswer(Bob,Alice,100)){
  //   cout << "More than 10 percent are the same" << endl;
  // }else{
  //   cout << "Less than 10 percent are the same" << endl;
  // }
  //
  // if(findRightAnswer(Bob,Alice,100)){
  //   cout << "RandAlg says more than 10 percent" << endl;
  // }else{
  //   cout << "RandAlg says less than 10 percent" << endl;
  // }

  return 0;
}
