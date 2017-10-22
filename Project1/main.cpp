#include "./prob.h"
#include "./naive.h"
#include <vector>
#include <iostream>

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
  std::vector<std::pair<double,double> > waypoints = createTravelVector();
  std::vector<int> list = naive::greedyTour(waypoints);
  std::vector<int> randlist = prob::compute(waypoints).first;
  for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << " " << randlist[i] << std::endl;
  }
  return 0;
}
