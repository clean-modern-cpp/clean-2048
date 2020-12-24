#include "BoardViewModel.h"

BoardViewModel::BoardViewModel(QObject *)
    : numbers(rows, std::vector<int>(columns, 0)) {
  srand(time(NULL));
}
