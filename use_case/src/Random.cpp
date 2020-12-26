#include "use_case/Random.h"

#include <cstdlib>

namespace use_case {

class RandomImpl : public Random {
 public:
  int next(int min, int max) { return std::rand() % (max - min + 1) + min; }
};

}  // namespace use_case
