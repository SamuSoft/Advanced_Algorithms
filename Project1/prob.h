
#ifndef prob_H
#define prob_H

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <tuple>
#include <algorithm>


//returns a random solution as a pair of solution list and total length

class prob{
  private:
    static std::vector<std::tuple<int,double,double> >  copyList(const std::vector<std::pair<double,double> >& input){
      std::vector<std::tuple<int,double,double> > retval(input.size());
      for (size_t i = 0; i < input.size(); i++) {
          retval[i] = std::tuple<int,double,double>(i,input[i].first, input[i].second);
      }
      return retval;
    }

    static std::pair<std::vector<int>,int> compTrip(const std::vector<std::tuple<int,double,double> >& trip){
      int retval = 0;
      std::vector<int> v(trip.size());
      v[0] = std::get<0>(trip[0]);
      for (size_t i = 1; i < trip.size(); i++) {
        v[i] = std::get<0>(trip[i]);
        retval += sqrt(
                        pow(std::get<1>(trip[i-1]) - std::get<1>(trip[i]),2) +
                        pow(std::get<2>(trip[i-1]) - std::get<2>(trip[i]),2)
                      );
      }

      return std::pair<std::vector<int>,int>(v,retval);
    }
    static std::pair<std::vector<int>,int> getRandOrd(const std::vector<std::pair<double,double> >& input){
      std::vector<std::tuple<int,double,double> > copy = copyList(input);
      std::random_shuffle(++copy.begin(),copy.end());
      return compTrip(copy);
    }
    // Best I can do to create a static class in C++
    prob(){}
  public:
    static std::pair<std::vector<int>,int> compute(const std::vector<std::pair<double,double> >& input){
      return getRandOrd(input);
    }
};
#endif
