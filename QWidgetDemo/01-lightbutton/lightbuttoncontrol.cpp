#include "lightbuttoncontrol.h"
#include <QMouseEvent>
#include <QPainter>


LightButtonControl::LightButtonControl(QWidget *parent) : QPushButton(parent)
{
    m_sText = "";
    m_textColor = QColor(255, 255, 255);
    m_alarmColor = QColor(255, 107, 107);
    m_normalColor = QColor(10, 10, 10);

    m_borderOutColorStart = QColor(255, 255, 255);
    m_borderOutColorEnd = QColor(166, 166, 166);

    m_borderInColorStart = QColor(166, 166, 166);
    m_borderInColorEnd = QColor(255, 255, 255);

    m_bgColor = QColor(100, 184, 255);

    m_isShowRect = false;
    m_isShowOverlay = true;
    m_overlayColor = QColor(255, 255, 255);

    m_isCanMove = false;
    this->installEventFilter(this);

    m_isAlarm = false;
    timerAlarm = new QTimer(this);
    connect(timerAlarm, SIGNAL(timeout()), this, SLOT(alarm()));
    timerAlarm->setInterval(500);

}

bool LightButtonControl::eventFilter(QObject *watched, QEvent *event)
{
    if (m_isCanMove) {
        static QPoint lastPoint;
        static bool pressed = false;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if (mouseEvent->type() == QEvent::MouseButtonPress) {
            if (this->rect().contains(mouseEvent->pos()) && (mouseEvent->button() == Qt::LeftButton)) {
                lastPoint = mouseEvent->pos();
                pressed = true;
            }
        } else if (mouseEvent->type() == QEvent::MouseMove && pressed) {
            int dx = mouseEvent->pos().x() - lastPoint.x();
            int dy = mouseEvent->pos().y() - lastPoint.y();
            this->move(this->x() + dx, this->y() + dy);
        } else if (mouseEvent->type() == QEvent::MouseButtonRelease && pressed) {
            pressed = false;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void LightButtonControl::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if (m_isShowRect) {
        //绘制矩形区域
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_bgColor);
        painter.drawRoundedRect(this->rect(), 5, 5);

        //绘制文字
        if (!m_sText.isEmpty()) {
            QFont font;
            font.setPixelSize(side - 20);
            painter.setFont(font);
            painter.setPen(m_textColor);
            painter.drawText(this->rect(), Qt::AlignCenter, m_sText);
        }
    } else {
        painter.translate(width / 2, height / 2);
        painter.scale(side / 200.0, side / 200.0);

        //绘制外边框
        drawBorderOut(&painter);
        //绘制内边框
        drawBorderIn(&painter);
        //绘制内部指示颜色
        drawBg(&painter);
        //绘制居中文字
        drawText(&painter);
        //绘制遮罩层
        drawOverlay(&painter);
    }
}

void LightButtonControl::drawBorderOut(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, m_borderOutColorStart);
    borderGradient.setColorAt(1, m_borderOutColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightButtonControl::drawBorderIn(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, m_borderInColorStart);
    borderGradient.setColorAt(1, m_borderInColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightButtonControl::drawBg(QPainter *painter)
{
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightButtonControl::drawText(QPainter *painter)
{
    if (m_sText.isEmpty()) {
        return;
    }

    int radius = 100;
    painter->save();

    QFont font;
    font.setPixelSize(85);
    painter->setFont(font);
    painter->setPen(m_textColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignCenter, m_sText);
    painter->restore();
}

void LightButtonControl::drawOverlay(QPainter *painter)
{
    if (!m_isShowOverlay) {
        return;
    }

    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆的部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    m_overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, m_overlayColor);
    m_overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, m_overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

QString LightButtonControl::getText() const
{
    return this->m_sText;
}

QColor LightButtonControl::getTextColor() const
{
    return this->m_textColor;
}

QColor LightButtonControl::getAlarmColor() const
{
    return this->m_alarmColor;
}

QColor LightButtonControl::getNormalColor() const
{
    return this->m_normalColor;
}

QColor LightButtonControl::getBorderOutColorStart() const
{
    return this->m_borderOutColorStart;
}

QColor LightButtonControl::getBorderOutColorEnd() const
{
    return this->m_borderOutColorEnd;
}

QColor LightButtonControl::getBorderInColorStart() const
{
    return this->m_borderInColorStart;
}

QColor LightButtonControl::getBorderInColorEnd() const
{
    return this->m_borderInColorEnd;
}

QColor LightButtonControl::getBgColor() const
{
    return this->m_bgColor;
}

bool LightButtonControl::getCanMove() const
{
    return this->m_isCanMove;
}

bool LightButtonControl::getShowRect() const
{
    return this->m_isShowRect;
}

bool LightButtonControl::getShowOverlay() const
{
    return this->m_isShowOverlay;
}

QColor LightButtonControl::getoverlayColor() const
{
    return this->m_overlayColor;
}

QSize LightButtonControl::sizeHint() const
{
    return QSize(100, 100);
}

QSize LightButtonControl::minimumSizeHint() const
{
    return QSize(10, 10);
}

void LightButtonControl::setText(const QString &text)
{
    if (this->m_sText != text) {
        this->m_sText = text;
        this->update();
    }
}

void LightButtonControl::setTextColor(const QColor &textColor)
{
    if (this->m_textColor != textColor) {
        this->m_textColor = textColor;
        this->update();
    }
}

void LightButtonControl::setAlarmColor(const QColor &alarmColor)
{
    if (this->m_alarmColor != alarmColor) {
        this->m_alarmColor = alarmColor;
        this->update();
    }
}

void LightButtonControl::setNormalColor(const QColor &normalColor)
{
    if (this->m_normalColor != normalColor) {
        this->m_normalColor = normalColor;
        this->update();
    }
}

void LightButtonControl::setBorderOutColorStart(const QColor &borderOutColorStart)
{
    if (this->m_borderOutColorStart != borderOutColorStart) {
        this->m_borderOutColorStart = borderOutColorStart;
        this->update();
    }
}

void LightButtonControl::setBorderOutColorEnd(const QColor &borderOutColorEnd)
{
    if (this->m_borderOutColorEnd != borderOutColorEnd) {
        this->m_borderOutColorEnd = borderOutColorEnd;
        this->update();
    }
}

void LightButtonControl::setBorderInColorStart(const QColor &borderInColorStart)
{
    if (this->m_borderInColorStart != borderInColorStart) {
        this->m_borderInColorStart = borderInColorStart;
        this->update();
    }
}

void LightButtonControl::setBorderInColorEnd(const QColor &borderInColorEnd)
{
    if (this->m_borderInColorEnd != borderInColorEnd) {
        this->m_borderInColorEnd = borderInColorEnd;
        this->update();
    }
}

void LightButtonControl::setBgColor(const QColor &bgColor)
{
    if (this->m_bgColor != bgColor) {
        this->m_bgColor = bgColor;
        this->update();
    }
}

void LightButtonControl::setCanMove(bool canMove)
{
    if (this->m_isCanMove != canMove) {
        this->m_isCanMove = canMove;
        this->update();
    }
}

void LightButtonControl::setShowRect(bool showRect)
{
    if (this->m_isShowRect != showRect) {
        this->m_isShowRect = showRect;
        this->update();
    }
}

void LightButtonControl::setShowOverlay(bool showOverlay)
{
    if (this->m_isShowOverlay != showOverlay) {
        this->m_isShowOverlay = showOverlay;
        this->update();
    }
}

void LightButtonControl::setoverlayColor(const QColor &m_overlayColor)
{
    if (this->m_overlayColor != m_overlayColor) {
        this->m_overlayColor = m_overlayColor;
        this->update();
    }
}

void LightButtonControl::setGreen()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(0, 166, 0));
}

void LightButtonControl::setRed()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(255, 0, 0));
}

void LightButtonControl::setYellow()
{
    m_textColor = QColor(25, 50, 7);
    setBgColor(QColor(238, 238, 0));
}

void LightButtonControl::setBlack()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(10, 10, 10));
}

void LightButtonControl::setGray()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(129, 129, 129));
}

void LightButtonControl::setBlue()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(0, 0, 166));
}

void LightButtonControl::setLightBlue()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(100, 184, 255));
}

void LightButtonControl::setLightRed()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(255, 107, 107));
}

void LightButtonControl::setLightGreen()
{
    m_textColor = QColor(255, 255, 255);
    setBgColor(QColor(24, 189, 155));
}

void LightButtonControl::startAlarm()
{
    if (!timerAlarm->isActive()) {
        timerAlarm->start();
    }
}

void LightButtonControl::stopAlarm()
{
    if (timerAlarm->isActive()) {
        timerAlarm->stop();
    }
}

void LightButtonControl::alarm()
{
    if (m_isAlarm) {
        m_textColor = QColor(255, 255, 255);
        m_bgColor = m_normalColor;
    } else {
        m_textColor = QColor(255, 255, 255);
        m_bgColor = m_alarmColor;
    }

    this->update();
    m_isAlarm = !m_isAlarm;
}
