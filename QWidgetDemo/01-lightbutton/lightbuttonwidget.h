#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "lightbuttoncontrol.h"

class LightButtonWidget : public QWidget
{
    Q_OBJECT

public:
    LightButtonWidget(QWidget *parent = nullptr);
    ~LightButtonWidget();

private:
    void InitForm();

private slots:
    void updateValue();

private:
    LightButtonControl* m_pLightButton1;
    LightButtonControl* m_pLightButton2;
    LightButtonControl* m_pLightButton3;

    int m_iType;
};
#endif // WIDGET_H
