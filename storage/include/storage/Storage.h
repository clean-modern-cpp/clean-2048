#ifndef CLEAN2048_STORAGE_STORAGE_H_
#define CLEAN2048_STORAGE_STORAGE_H_

#include "use_case_interface/Storage.h"

namespace storage {

class Storage : public use_case_interface::Storage {
 public:
  use_case_interface::GameData loadGame() override;

  void saveGame(const use_case_interface::GameData& gameData) override;

  void clear() override;
};

}  // namespace storage

#endif
