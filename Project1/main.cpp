#include "./prob.h"
#include "./naive.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>

std::vector<std::pair<double,double> > waypoints;

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
    retval += (int) sqrt(
                    pow(data[trip[i-1]].first - data[trip[i]].first,2) +
                    pow(data[trip[i-1]].second - data[trip[i]].second,2)
                  );
  }
  return retval;
}

std::vector<int> swapper(std::vector<int> list){
  std::vector<int>::iterator a = list.begin(); std::vector<int>::iterator b = ++list.begin();
  int len = length(list);
  int newlen = len;
  auto print = [](std::vector<int> l){for(int x : l){std::cout<<l[x]<<" ";} std::cout<<std::endl;};
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

int main(int argc, char const *argv[]) {
  // number of random solution samples
  int count = 50;


  srand(time(NULL));

  waypoints = createTravelVector();
  auto list = naive::greedyTour(waypoints);
  std::vector<int> randlist;
  std::vector<int> truelist;

  int cost = 99999;
  int lcost;
  for (size_t i = 0; i < count; i++) {
    randlist = prob::getRandList(waypoints);
    lcost = length(randlist);
    if (lcost < cost) {
      truelist = randlist;
      cost = lcost;
    }
  }

  auto reflist = swapper(truelist);
  std::cout << "Greedy:\tProb:\tSwapped:"<< std::endl;
  std::cout << length(list) << "\t" << length(truelist) << "\t"<< length(reflist)<< std::endl;
  for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << "\t" << truelist[i] << "\t" << reflist[i] << std::endl;
  }
  return 0;
}
