#include "./prob.h"
// #include "./naive.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <cmath>

std::vector<std::pair<double,double> > waypoints;

std::vector<std::vector<int> > dist;

std::vector<std::pair<double,double> > createTravelVector(){
  int len;
  std::cin >> len;
  std::vector<std::pair<double,double> > list(len);
  double x,y;
  for (size_t i = 0; i < len; i++) {
    std::cin >> x >> y;
    list[i] = std::pair<double,double>(x,y);
  }
  return list;
}

int length(std::vector<int> trip){
  auto data = waypoints;
  int retval = 0;
  for (size_t i = 1; i < trip.size(); i++){
    retval += (int) dist[trip[i-1]][trip[i]];
    // sqrt(
    //                 pow(data[trip[i-1]].first - data[trip[i]].first,2) +
    //                 pow(data[trip[i-1]].second - data[trip[i]].second,2)
    //               );
  }
  return retval;
}

std::vector<int> swapper(std::vector<int> list){
  std::vector<int>::iterator a = list.begin(); std::vector<int>::iterator b = ++list.begin();
  int len = length(list);
  int newlen = len;
  auto print = [](std::vector<int> l){for(int x : l){std::cout<<l[x]<<" ";} std::cout<<"\n";};
  for(int a = 1; a < list.size(); a++) {
    for(int b = a+1; b < list.size(); b++){
      std::swap(list[a],list[b]);
      newlen = length(list);
      if(newlen < len){
        a = 0; len = newlen; break;
      }else {
        std::swap(list[a],list[b]);
      }
    }
  }
  return list;
}

int distance(int i, int j){
  return dist[i][j];



}


void initDist(){
  int N = waypoints.size();
  dist.resize(N);
  for (int i = 0; i < N; ++i) {
    dist[i].resize(N, 0);

    for (int j = 0; j < N; ++j) {
      dist[i][j] = sqrt(
        pow(waypoints[i].first - waypoints[j].first,2) +
        pow(waypoints[i].second - waypoints[j].second,2));
    }
  }
}

int main(int argc, char const *argv[]) {
  // number of random solution samples
  int count = 1;


  srand(time(NULL));

  waypoints = createTravelVector();
  initDist();
  // auto list = naive::greedyTour(waypoints);
  std::vector<int> randlist;
  std::vector<int> truelist;

  int cost = 99999;
  int lcost;
  for (size_t i = 0; i < count; i++) {
    randlist = prob::getRandList(waypoints);
    randlist = swapper(randlist);
    lcost = length(randlist);
    if (lcost < cost) {
      truelist = randlist;
      cost = lcost;
    }
  }

  // auto reflist = swapper(truelist);
  // std::cout << "Greedy:\tProb:\tSwapped:"<< "\n";
  // std::cout << length(list) << "\t" << length(truelist) << "\t"<< length(reflist)<< "\n";
  for (int i : randlist) {
    std::cout << randlist[i] << "\n";// << truelist[i] << "\t" << reflist[i] << "\n";
  }
  return 0;
}
