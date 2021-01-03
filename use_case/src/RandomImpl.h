#ifndef CLEAN2048_USECASE_RANDOMIMPL_H_
#define CLEAN2048_USECASE_RANDOMIMPL_H_

#include <random>

#include "use_case/Random.h"

namespace use_case {

class RandomImpl : public Random {
 public:
  RandomImpl() : gen{rd()} {}

  int next(int min, int max) override {
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
  }

 private:
  std::random_device rd;
  std::mt19937 gen;
};

}  // namespace use_case

#endif
