#include "qt_view_model/BoardViewModel.h"

namespace qt_view_model {

BoardViewModel::BoardViewModel(QObject *) { boardPresenter.setDelegate(this); }

}  // namespace qt_view_model
