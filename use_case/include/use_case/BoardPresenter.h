#ifndef CLEAN2048_USECASE_BOARDPRESENTER_H_
#define CLEAN2048_USECASE_BOARDPRESENTER_H_

#include "common/NonCopyable.h"
#include "use_case/Model.h"

namespace use_case {

class BoardPresenter : public common::NonCopyable {
 public:
  virtual void initWithDimension(int row, int column) const = 0;
  virtual void present(use_case::Actions actions) const = 0;
};

void setBoardPresenter(const BoardPresenter* presenter);

}  // namespace use_case

#endif
