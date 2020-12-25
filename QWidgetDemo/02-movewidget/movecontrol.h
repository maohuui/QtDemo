#ifndef MOVECONTROL_H
#define MOVECONTROL_H

#include <QWidget>
#include <QPoint>
#include <QObject>

class MoveControl : public QWidget
{
    Q_OBJECT
public:
    explicit MoveControl(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QPoint m_lastPoint;   //最后按下的坐标
    bool m_isPressed;       //鼠标是否按下
    bool m_isLeftButton;    //限定鼠标左键
    bool m_isInControl;     //限定在容器内
    QWidget *m_pWidget;    //移动的控件

public Q_SLOTS:
    void setLeftButton(bool leftButton);//设置是否限定鼠标左键
    void setInControl(bool inControl);//设置是否限定不能移出容器外面
    void setWidget(QWidget *widget);//设置要移动的控件

};

#endif // MOVECONTROL_H
