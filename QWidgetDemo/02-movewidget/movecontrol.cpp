#include "movecontrol.h"
#include <QMouseEvent>


MoveControl::MoveControl(QWidget *parent) : QWidget(parent)
{
    m_lastPoint = QPoint(0, 0);
    m_isPressed = false;
    m_isLeftButton = true;
    m_isInControl = true;
    m_pWidget = 0;
}

bool MoveControl::eventFilter(QObject *watched, QEvent *event)
{
    if (m_pWidget != 0 && watched == m_pWidget) {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->type() == QEvent::MouseButtonPress) {
            //如果限定了只能鼠标左键拖动则判断当前是否是鼠标左键
            if (m_isLeftButton && mouseEvent->button() != Qt::LeftButton) {
                return false;
            }

            //判断控件的区域是否包含了当前鼠标的坐标
            if (m_pWidget->rect().contains(mouseEvent->pos())) {
                m_lastPoint = mouseEvent->pos();
                m_isPressed = true;
            }
        } else if (mouseEvent->type() == QEvent::MouseMove && m_isPressed) {
            //计算坐标偏移值,调用move函数移动过去
            int offsetX = mouseEvent->pos().x() - m_lastPoint.x();
            int offsetY = mouseEvent->pos().y() - m_lastPoint.y();
            int x = m_pWidget->x() + offsetX;
            int y = m_pWidget->y() + offsetY;
            if (m_isInControl) {
                //可以自行调整限定在容器中的范围,这里默认保留20个像素在里面
                int offset = 20;
                bool xyOut = (x + m_pWidget->width() < offset || y + m_pWidget->height() < offset);
                bool whOut = false;
                QWidget *w = (QWidget *)m_pWidget->parent();
                if (w != 0) {
                    whOut = (w->width() - x < offset || w->height() - y < offset);
                }
                if (xyOut || whOut) {
                    return false;
                }
            }

            m_pWidget->move(x, y);
        } else if (mouseEvent->type() == QEvent::MouseButtonRelease && m_isPressed) {
            m_isPressed = false;
        }
    }

    return QObject::eventFilter(watched, event);
}

void MoveControl::setWidget(QWidget *widget)
{
    if (this->m_pWidget == 0) {
        this->m_pWidget = widget;
        this->m_pWidget->installEventFilter(this);
    }
}

void MoveControl::setLeftButton(bool leftButton)
{
    this->m_isLeftButton = leftButton;
}

void MoveControl::setInControl(bool inControl)
{
    this->m_isInControl = inControl;
}
