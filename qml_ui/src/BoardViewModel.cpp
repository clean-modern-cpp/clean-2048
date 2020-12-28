#include "BoardViewModel.h"

BoardViewModel::BoardViewModel(QObject *) { boardPresenter.setDelegate(this); }
