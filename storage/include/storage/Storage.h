#ifndef CLEAN2048_STORAGE_STORAGE_H_
#define CLEAN2048_STORAGE_STORAGE_H_

#include "use_case/Storage.h"

namespace storage {

class Storage : public use_case::Storage {
 public:
  use_case::GameData loadGame() override;

  void saveGame(const use_case::GameData& gameData) override;

  void clear() override;
};

}  // namespace storage

#endif
