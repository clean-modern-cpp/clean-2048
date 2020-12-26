#ifndef CLEAN2048_USECASE_RANDOMIMPL_H_
#define CLEAN2048_USECASE_RANDOMIMPL_H_

#include <cstdlib>

#include "use_case/Random.h"

namespace use_case {

class RandomImpl : public Random {
 public:
  RandomImpl() { std::srand(time(0)); }

  int next(int min, int max) override {
    return std::rand() % (max - min + 1) + min;
  }
};

}  // namespace use_case

#endif
