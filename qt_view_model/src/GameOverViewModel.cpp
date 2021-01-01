#include "qt_view_model/GameOverViewModel.h"

namespace qt_view_model {

GameOverViewModel::GameOverViewModel(QObject *) {
  gameOverPresenter.setDelegate(this);
}

}  // namespace qt_view_model
