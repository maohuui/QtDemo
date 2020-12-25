#ifndef COUNTCODEWIDGET_H
#define COUNTCODEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class CountCodeWidget : public QWidget
{
    Q_OBJECT

public:
    CountCodeWidget(QWidget *parent = nullptr);
    ~CountCodeWidget();

private:
    void initForm();
    void setPropery();
};
#endif // COUNTCODEWIDGET_H
