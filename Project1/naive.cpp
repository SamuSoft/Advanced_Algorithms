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

std::vector<int> greedyTour(const std::vector<std::pair<double,double> >& list){
  // tour[0] = 0
  // used[0] = true
  // for i = 1 to n-1
  //   best = -1
  //   for j = 0 to n-1
  //     if not used[j] and (best = -1 or dist(tour[i-1],j) < dist(tour[i-1],best))
  //     best = j
  //   tour[i] = best
  //   used[best] = true
  // return tour
  std::vector<int> first(1);
  return first;
}

int main(int argc, char const *argv[]) {
  std::vector<std::pair<double,double> > list = createTravelVector();
  for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i].first << ' ' << list[i].second << std::endl;
  }
  return 0;
}
