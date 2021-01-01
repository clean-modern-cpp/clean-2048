#ifndef CLEAN2048_USECASE_RANDOM_H_
#define CLEAN2048_USECASE_RANDOM_H_

#include <memory>

#include "common/NonCopyable.h"

namespace use_case {

class Random : public common::NonCopyable {
 public:
  virtual int next(int min, int max) = 0;
};

void setRandom(const std::unique_ptr<Random> random);

}  // namespace use_case

#endif
