// #include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget)
{
  ui->setupUi(this);

  setAttribute(Qt::WA_TranslucentBackground);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

  ui->verticalLayout_2->addStretch();
  ui->label->setFixedSize(QSize(48, 48));

  for (int i=0; i<50; i++) {
    auto pushButton = new QPushButton(ui->scrollAreaWidgetContents);
    pushButton->setObjectName(QString::fromUtf8("pushButton__%1").arg(i));
    pushButton->setText(QApplication::translate("Widget", "PushButton", nullptr));

    ui->verticalLayout_2->addWidget(pushButton);
  }
}

Widget::~Widget()
{
  delete ui;
}

void Widget::show() {
  // int w_width = QApplication::desktop()->availableGeometry().width() / 5;
  int w_height = QApplication::desktop()->availableGeometry().height();
  resize(width(), w_height);

  setGeometry(QApplication::desktop()->availableGeometry().width() - width() + QApplication::desktop() -> availableGeometry().x(),
                QApplication::desktop() -> availableGeometry().y(),
                width(),
                height());
  QWidget::show();
}
