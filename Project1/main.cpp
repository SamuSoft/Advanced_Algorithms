#include "./prob.h"
#include "./naive.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>

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

int main(int argc, char const *argv[]) {
  // number of random solution samples
  int count = 50;


  srand(time(NULL));

  std::vector<std::pair<double,double> > waypoints = createTravelVector();
  std::vector<int> list = naive::greedyTour(waypoints);
  std::pair<std::vector<int>,int> randlist;
  std::vector<int> truelist;

  int cost = 99999;
  for (size_t i = 0; i < count; i++) {
    randlist = prob::compute(waypoints);
    if (randlist.second < cost) {
      truelist = randlist.first;
      cost = randlist.second;
    }
  }

  for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << " " << truelist[i] << std::endl;
  }
  return 0;
}
