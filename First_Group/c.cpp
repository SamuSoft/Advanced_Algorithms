#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>


using namespace std;


vector<pair<int,int> > createGraph(int n, int m){
  vector<pair<int,int> > G(m);
  int a;
  int b;
  for (size_t i = 0; i < m; i++) {
    a = 0;
    b = 0;
    //The while makes it impossible to circle link or double link
    while(a == b
      || find(G.begin(),G.end(), pair<int,int>(a,b)) != G.end()
      || find(G.begin(),G.end(), pair<int,int>(b,a)) != G.end()){
      a = rand()%n;
      b = rand()%n;
    }
    G[i] = pair <int,int> (a,b);
  }
  return G;
}

void printGraph(const vector<pair<int,int> >& G){
  for (size_t i = 0; i < G.size(); i++) {
    cout << "("<< G[i].first << "," << G[i].second << ")" << endl;
  }
}



int main(int argc, char const *argv[]) {
  vector<pair<int,int> > G = createGraph(5,5);
  printGraph(G);
  return 0;
}
