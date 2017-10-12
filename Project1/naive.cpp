#include <vector>
#include <iostream>
#include <cmath>


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

double dist(const std::pair<double,double>& a, const std::pair<double,double>& b){
  double xval = a.first - b.first; xval = xval*xval;
  double yval = a.second - b.second; yval = yval*yval;
  return sqrt(xval+yval);
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

  std::vector<int> tour(list.size());
  std::vector<bool> used(list.size());
  tour[0]=0;
  used[0]=true;
  int best;
  for (size_t i = 1; i < list.size(); i++) {
    best = -1;
    for (size_t j = 0; j < list.size(); j++) {
      if (!used[j] && (best == -1 || dist(list[tour[i-1]],list[j]) < dist(list[tour[i-1]],list[best]))) {
        best = j;
      }
    }
    tour[i] = best;
    used[best]=true;
  }
  return tour;
}

int main(int argc, char const *argv[]) {
  std::vector<std::pair<double,double> > waypoints = createTravelVector();
  std::vector<int> list = greedyTour(waypoints);
  for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << std::endl;
  }
  return 0;
}
