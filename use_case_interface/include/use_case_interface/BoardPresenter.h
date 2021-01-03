#ifndef CLEAN2048_USECASEINTERFACE_BOARDPRESENTER_H_
#define CLEAN2048_USECASEINTERFACE_BOARDPRESENTER_H_

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case_interface {

class BoardPresenter : public common::NonCopyable {
 public:
  virtual void initWithDimension(int row, int column) = 0;
  virtual void present(common::Actions actions) = 0;
};

}  // namespace use_case_interface

#endif
