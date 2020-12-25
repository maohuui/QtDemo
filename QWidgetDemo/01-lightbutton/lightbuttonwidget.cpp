#include "lightbuttonwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGradient>

LightButtonWidget::LightButtonWidget(QWidget *parent)
    : QWidget(parent)
{
    this->InitForm();

    m_iType = 0;

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

LightButtonWidget::~LightButtonWidget()
{

}


void LightButtonWidget::InitForm()
{
    QWidget* widget = new QWidget(this);

    QHBoxLayout* layout = new QHBoxLayout;

    m_pLightButton1 = new LightButtonControl(this);
    m_pLightButton2 = new LightButtonControl(this);
    m_pLightButton3 = new LightButtonControl(this);


    layout->addWidget(m_pLightButton1);
    layout->addWidget(m_pLightButton2);
    layout->addWidget(m_pLightButton3);

    widget->setLayout(layout);
    this->setLayout(layout);
    this->setGeometry(10, 10, 500, 300);
}

void LightButtonWidget::updateValue()
{
    if (m_iType == 0) {
        m_pLightButton1->setLightGreen();
        m_pLightButton2->setLightRed();
        m_pLightButton3->setLightBlue();
        m_iType = 1;
    } else if (m_iType == 1) {
        m_pLightButton1->setLightBlue();
        m_pLightButton2->setLightGreen();
        m_pLightButton3->setLightRed();
        m_iType = 2;
    } else if (m_iType == 2) {
        m_pLightButton1->setLightRed();
        m_pLightButton2->setLightBlue();
        m_pLightButton3->setLightGreen();
        m_iType = 0;
    }
}
