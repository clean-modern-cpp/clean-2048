#ifndef CLEAN2048_PRESENTER_CONTROLLER_H_
#define CLEAN2048_PRESENTER_CONTROLLER_H_

#include <memory>

namespace presenter {

class Controller {
 public:
  Controller();
  ~Controller();

  void newGame();

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace presenter

#endif
