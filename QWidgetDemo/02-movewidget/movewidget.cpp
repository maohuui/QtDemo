#include "movewidget.h"
#include "movecontrol.h"
#include <QPushButton>
#include <QProgressBar>

MoveWidget::MoveWidget(QWidget *parent)
    : QWidget(parent)
{
    this->InitForm();
}

MoveWidget::~MoveWidget()
{
}

void MoveWidget::InitForm()
{
    QPushButton *btn1 = new QPushButton(this);
    btn1->setGeometry(10, 10, 250, 25);
    btn1->setText("按住我拖动(仅限左键拖动)");
    MoveControl *moveWidget1 = new MoveControl(this);
    moveWidget1->setWidget(btn1);

    QPushButton *btn2 = new QPushButton(this);
    btn2->setGeometry(10, 40, 250, 25);
    btn2->setText("按住我拖动(支持右键拖动)");
    MoveControl *moveWidget2 = new MoveControl(this);
    moveWidget2->setWidget(btn2);
    moveWidget2->setLeftButton(false);

    QProgressBar *bar = new QProgressBar(this);
    bar->setGeometry(10, 70, 250, 25);
    bar->setRange(0, 0);
    bar->setTextVisible(false);
    MoveControl *moveWidget3 = new MoveControl(this);
    moveWidget3->setWidget(bar);

    this->setGeometry(10, 10, 500, 300);
}
