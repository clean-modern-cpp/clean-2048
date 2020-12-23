#ifndef CLEAN2048_USECASE_BOARDPRESENTER_H_
#define CLEAN2048_USECASE_BOARDPRESENTER_H_

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case {

class BoardPresenter : public common::NonCopyable {
 public:
  virtual void initWithDimension(int row, int column) = 0;
  virtual void presentActions(common::model::Actions actions) = 0;
};

}  // namespace use_case

#endif
