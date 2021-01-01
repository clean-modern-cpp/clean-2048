#ifndef CLEAN2048_STORAGE_STORAGE_H_
#define CLEAN2048_STORAGE_STORAGE_H_

#include "use_case/Storage.h"

namespace storage {

class Storage : public use_case::Storage {
 public:
  use_case::ScoreData loadScore() override;
  use_case::BoardData loadBoard() override;

  void saveScore(const use_case::ScoreData& scoreData) override;
  void saveBoard(const use_case::BoardData& boardData) override;

  void clear() override;
};

}  // namespace storage

#endif
