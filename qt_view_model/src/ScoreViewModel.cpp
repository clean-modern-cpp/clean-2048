#include "qt_view_model/ScoreViewModel.h"

namespace qt_view_model {

ScoreViewModel::ScoreViewModel(QObject *) { scorePresenter.setDelegate(this); }

}  // namespace qt_view_model
