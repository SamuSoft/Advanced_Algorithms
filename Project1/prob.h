
#ifndef prob_H
#define prob_H

#include <vector>
#include <algorithm>

//returns a random solution as a pair of solution list and total length

class prob{
  private:
    prob(){}
  public:
    static std::vector<int> getRandList(const std::vector<std::pair<double,double> >& input){
      std::vector<int> retval(input.size());
      std::iota(retval.begin(), retval.end(),0);
      std::random_shuffle(++retval.begin(),retval.end());
      return retval;
    }
};
#endif
