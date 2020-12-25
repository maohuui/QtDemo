#ifndef FLATUIWIDGET_H
#define FLATUIWIDGET_H

#include <QWidget>
#include "flatuicontrol.h"
#include <QTableWidget>
#include <QScrollBar>
#include <QDateTime>
#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>

class FlatUiWidget : public QWidget
{
    Q_OBJECT

public:
    FlatUiWidget(QWidget *parent = nullptr);
    ~FlatUiWidget();

private:
    void initForm();
    void setPropery();

private:
    QPushButton* m_pPushButton1;
    QPushButton* m_pPushButton2;
    QPushButton* m_pPushButton3;
    QPushButton* m_pPushButton4;

    QLineEdit* m_pLienEdit1;
    QLineEdit* m_pLienEdit2;
    QLineEdit* m_pLienEdit3;
    QLineEdit* m_pLienEdit4;

    QProgressBar* m_pBar1;
    QProgressBar* m_pBar2;
    QSlider* m_pHslider1;
    QSlider* m_pHslider2;
    QSlider* m_pVslider3;

    QScrollBar*  m_pHscrollBar;
    QScrollBar*  m_pVscrollBar;

    QRadioButton* m_pRadioButton1;
    QRadioButton* m_pRadioButton2;
    QRadioButton* m_pRadioButton3;
    QRadioButton* m_pRadioButton4;

    QTableWidget* m_pTableWidget;
};
#endif // FLATUIWIDGET_H
