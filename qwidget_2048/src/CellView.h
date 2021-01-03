#ifndef CLEAN2048_QWIDGETUI_CELLVIEW_H_
#define CLEAN2048_QWIDGETUI_CELLVIEW_H_

#include <QWidget>

namespace Ui {
class CellView;
}

class CellView : public QWidget {
  Q_OBJECT

 public:
  explicit CellView(QWidget *parent = nullptr);
  ~CellView();

  void setText(const QString &value);

 private:
  Ui::CellView *ui;
};

#endif
