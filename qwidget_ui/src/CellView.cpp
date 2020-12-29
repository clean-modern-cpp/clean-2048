#include "CellView.h"

#include <QPropertyAnimation>

#include "ui_CellView.h"

CellView::CellView(QWidget *parent) : QWidget(parent), ui(new Ui::CellView) {
  ui->setupUi(this);
}

CellView::~CellView() { delete ui; }

void CellView::setText(const QString &value) { ui->label->setText(value); }
