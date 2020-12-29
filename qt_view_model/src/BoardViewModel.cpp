#include "qt_view_model/BoardViewModel.h"

BoardViewModel::BoardViewModel(QObject *) { boardPresenter.setDelegate(this); }
