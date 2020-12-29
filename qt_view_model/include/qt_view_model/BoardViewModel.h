#ifndef CLEAN2048_QTVIEWMODEL_BOARDVIEWMODEL_H_
#define CLEAN2048_QTVIEWMODEL_BOARDVIEWMODEL_H_

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <QKeyEvent>
#include <QObject>
#include <QString>
#include <QTimer>
#include <unordered_map>
#include <vector>

#include "common/ModelHelper.h"
#include "presenter/BoardPresenter.h"
#include "presenter/Controller.h"

namespace qt_view_model {

class BoardViewModel : public QObject, presenter::BoardPresenterDelegate {
  Q_OBJECT

  Q_PROPERTY(int rows MEMBER rows NOTIFY rowsChanged)
  Q_PROPERTY(int columns MEMBER columns NOTIFY columnChanged)

 public:
  explicit BoardViewModel(QObject* parent = nullptr);

  void intiWithDimension(int row, int col) override {
    spdlog::info("row: {}, col: {}", row, col);
  }

  void present(common::Actions actions) override {
    spdlog::info("present actions: {}", actions);
    for (const auto& [from, to] : actions.moveActions) {
      emit startCellMove(from.row, from.col, to.row, to.col);
    }
    QTimer::singleShot(100, [this, actions = std::move(actions)]() {
      for (const auto& [from, to] : actions.moveActions) {
        if (from != to) {
          emit completeCellMove(from.row, from.col, to.row, to.col);
        }
      }
      for (const auto& [pos, value] : actions.newActions) {
        emit newCell(pos.row, pos.col, QString::number(value));
      }
      for (const auto& [pos, from, to] : actions.changeActions) {
        emit changeCell(pos.row, pos.col, QString::number(to));
      }
    });
  }

  Q_INVOKABLE void restart() { controller.newGame(); }

  Q_INVOKABLE void swipe(int key) { controller.swipe(directionMap.at(key)); }

 signals:
  void rowsChanged();
  void columnChanged();

  void newCell(int row, int col, QString value);
  void startCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void completeCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void changeCell(int row, int col, QString value);

 private:
  int rows = 4;
  int columns = 4;

  presenter::Controller controller;
  presenter::BoardPresenter boardPresenter;

  inline static const std::unordered_map<int, common::Direction> directionMap{
      {Qt::Key_Left, common::Direction::left},
      {Qt::Key_Right, common::Direction::right},
      {Qt::Key_Up, common::Direction::up},
      {Qt::Key_Down, common::Direction::down},
  };
};

}  // namespace qt_view_model

#endif
