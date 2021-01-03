#ifndef CLEAN2048_USECASEINTERFACE_RANDOM_H_
#define CLEAN2048_USECASEINTERFACE_RANDOM_H_

#include <memory>

#include "common/NonCopyable.h"

namespace use_case_interface {

class Random : public common::NonCopyable {
 public:
  virtual int next(int min, int max) = 0;
};

}  // namespace use_case_interface

#endif
