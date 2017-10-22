#ifndef naive_H
#define naive_H
#include <vector>
#include <cmath>


class naive{
  private:
    naive(){}

    static double dist(const std::pair<double,double>& a, const std::pair<double,double>& b){
      double xval = a.first - b.first; xval = xval*xval;
      double yval = a.second - b.second; yval = yval*yval;
      return sqrt(xval+yval);
    }
  public:
    static std::vector<int> greedyTour(const std::vector<std::pair<double,double> >& list){
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
};
#endif
