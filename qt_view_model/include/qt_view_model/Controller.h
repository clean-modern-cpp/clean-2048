#ifndef CLEAN2048_QTVIEWMODEL_CONTROLLER_H_
#define CLEAN2048_QTVIEWMODEL_CONTROLLER_H_

#include <QObject>
#include <unordered_map>

#include "presenter/Controller.h"

namespace qt_view_model {

class Controller : public QObject {
  Q_OBJECT

 public:
  explicit Controller(QObject* parent = nullptr);

  Q_INVOKABLE void newGame() { controller.newGame(); }

  Q_INVOKABLE void loadGame() { controller.loadGame(); }

  Q_INVOKABLE void saveGame() { controller.saveGame(); }

  Q_INVOKABLE void swipe(int key) {
    if (directionMap.find(key) != directionMap.end()) {
      controller.swipe(directionMap.at(key));
    }
  }

 private:
  presenter::Controller controller;

  inline static const std::unordered_map<int, common::Direction> directionMap{
      {Qt::Key_Left, common::Direction::left},
      {Qt::Key_Right, common::Direction::right},
      {Qt::Key_Up, common::Direction::up},
      {Qt::Key_Down, common::Direction::down},
  };
};

}  // namespace qt_view_model

#endif
