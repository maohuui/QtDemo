#ifndef MOVEWIDGET_H
#define MOVEWIDGET_H

#include <QWidget>

class MoveWidget : public QWidget
{
    Q_OBJECT

public:
    MoveWidget(QWidget *parent = nullptr);
    ~MoveWidget();

private:
    void InitForm();

};
#endif // MOVEWIDGET_H
