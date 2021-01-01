#ifndef CLEAN2048_STORAGE_STORAGE_H_
#define CLEAN2048_STORAGE_STORAGE_H_

#include "use_case/Storage.h"

namespace storage {

class Storage : public use_case::Storage {
 public:
  use_case::ScoreStorage loadScore() override;
  use_case::BoardStorage loadBoard() override;

  void saveScore(const use_case::ScoreStorage& scoreStorage) override;
  void saveBoard(const use_case::BoardStorage& boardStorage) override;
};

}  // namespace storage

#endif
