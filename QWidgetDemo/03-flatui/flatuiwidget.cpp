#include "flatuiwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

FlatUiWidget::FlatUiWidget(QWidget *parent)
    : QWidget(parent)
{
    this->initForm();
    this->setPropery();
}

FlatUiWidget::~FlatUiWidget()
{
}

void FlatUiWidget::initForm()
{
    QVBoxLayout* layout = new QVBoxLayout;
    {
        QHBoxLayout* hLayout = new QHBoxLayout;
        {
            QVBoxLayout* vLayout = new QVBoxLayout;
            {
                QGridLayout* top_gLayout = new QGridLayout;
                m_pPushButton1 = new QPushButton(this);
                m_pPushButton2 = new QPushButton(this);
                m_pPushButton3 = new QPushButton(this);
                m_pPushButton4 = new QPushButton(this);
                m_pLienEdit1 = new QLineEdit(this);
                m_pLienEdit2 = new QLineEdit(this);
                m_pLienEdit3 = new QLineEdit(this);
                m_pLienEdit4 = new QLineEdit(this);

                m_pPushButton1->setText("测试按钮1");
                m_pPushButton2->setText("测试按钮2");
                m_pPushButton3->setText("测试按钮3");
                m_pPushButton4->setText("测试按钮4");

                top_gLayout->addWidget(m_pPushButton1, 0, 0);
                top_gLayout->addWidget(m_pPushButton2, 0, 1);
                top_gLayout->addWidget(m_pPushButton3, 0, 2);
                top_gLayout->addWidget(m_pPushButton4, 0, 3);
                top_gLayout->addWidget(m_pLienEdit1, 1, 0);
                top_gLayout->addWidget(m_pLienEdit2, 1, 1);
                top_gLayout->addWidget(m_pLienEdit3, 1, 2);
                top_gLayout->addWidget(m_pLienEdit4, 1, 3);
                top_gLayout->setSpacing(2); //设置每个控件之间的距离
                top_gLayout->setMargin(0);
                vLayout->addLayout(top_gLayout);
            }
            {
                QGridLayout* middle_gLayout = new QGridLayout;
                m_pBar1 = new QProgressBar(this);
                m_pBar2 = new QProgressBar(this);
                m_pHslider1 = new QSlider(Qt::Horizontal,this);
                m_pHslider2 = new QSlider(Qt::Horizontal,this);
                m_pHscrollBar = new QScrollBar(Qt::Horizontal, this);

                middle_gLayout->addWidget(m_pBar1, 0, 0);
                middle_gLayout->addWidget(m_pBar2, 0, 1);
                middle_gLayout->addWidget(m_pHslider1, 1, 0);
                middle_gLayout->addWidget(m_pHslider2, 1, 1);
                middle_gLayout->addWidget(m_pHscrollBar, 2, 0, 1, 2);
                middle_gLayout->setMargin(0);
                vLayout->addLayout(middle_gLayout);
            }
            {
                QHBoxLayout* middle_hLayout = new QHBoxLayout;
                m_pRadioButton1 = new QRadioButton(this);
                m_pRadioButton2 = new QRadioButton(this);
                m_pRadioButton3 = new QRadioButton(this);
                m_pRadioButton4 = new QRadioButton(this);

                m_pRadioButton1->setText("语文");
                m_pRadioButton2->setText("英语");
                m_pRadioButton3->setText("数学");
                m_pRadioButton4->setText("历史");

                middle_hLayout->addWidget(m_pRadioButton1);
                middle_hLayout->addWidget(m_pRadioButton2);
                middle_hLayout->addWidget(m_pRadioButton3);
                middle_hLayout->addWidget(m_pRadioButton4);
                middle_hLayout->setMargin(0);
                vLayout->addLayout(middle_hLayout);
            }
            vLayout->setMargin(0);
            hLayout->addLayout(vLayout);
        }
        {
            m_pVslider3 = new QSlider(Qt::Vertical,this);
            m_pVscrollBar = new QScrollBar(Qt::Vertical, this);
            hLayout->addWidget(m_pVslider3);
            hLayout->addWidget(m_pVscrollBar);
        }
        hLayout->setMargin(0);
        layout->addLayout(hLayout);
        layout->addStretch();
    }

    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setMinimumSize(80, 600);
    layout->setMargin(1);
    layout->addWidget(m_pTableWidget);
    layout->addStretch();

    this->setLayout(layout);
    this->setGeometry(100, 100, 800, 600);
}

void FlatUiWidget::setPropery()
{
    this->m_pBar1->setRange(0, 100);
    this->m_pBar2->setRange(0, 100);
    this->m_pHslider1->setRange(0, 100);
    this->m_pHslider2->setRange(0, 100);

    connect(this->m_pHslider1, &QSlider::valueChanged, this->m_pBar1, &QProgressBar::setValue);
    connect(this->m_pHslider2, &QSlider::valueChanged, this->m_pBar2, &QProgressBar::setValue);

    this->m_pHslider1->setValue(30);
    this->m_pHslider2->setValue(30);

    this->setStyleSheet("*{outline:0px;}QWidget#frmFlatUI{background:#FFFFFF;}");

    FlatUiControl::setPushButtonQss(m_pPushButton1);
    FlatUiControl::setPushButtonQss(m_pPushButton2, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUiControl::setPushButtonQss(m_pPushButton3, 5, 8, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    FlatUiControl::setPushButtonQss(m_pPushButton4, 5, 8, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");

    FlatUiControl::setLineEditQss(m_pLienEdit1);
    FlatUiControl::setLineEditQss(m_pLienEdit2, 5, 2, "#DCE4EC", "#1ABC9C");
    FlatUiControl::setLineEditQss(m_pLienEdit3, 3, 1, "#DCE4EC", "#3498DB");
    FlatUiControl::setLineEditQss(m_pLienEdit4, 3, 1, "#DCE4EC", "#E74C3C");

    FlatUiControl::setProgressQss(m_pBar1);
    FlatUiControl::setProgressQss(m_pBar2, 8, 5, 9, "#E8EDF2", "#1ABC9C");
    FlatUiControl::setSliderQss(m_pHslider1);
    FlatUiControl::setSliderQss(m_pHslider1, 10, "#E8EDF2", "#E74C3C", "#E74C3C");
    FlatUiControl::setSliderQss(m_pVslider3, 10, "#E8EDF2", "#34495E", "#34495E");

    FlatUiControl::setRadioButtonQss(m_pRadioButton1);
    FlatUiControl::setRadioButtonQss(m_pRadioButton2, 8, "#D7DBDE", "#1ABC9C");
    FlatUiControl::setRadioButtonQss(m_pRadioButton3, 8, "#D7DBDE", "#3498DB");
    FlatUiControl::setRadioButtonQss(m_pRadioButton4, 8, "#D7DBDE", "#E74C3C");

    FlatUiControl::setScrollBarQss(m_pHscrollBar);
    FlatUiControl::setScrollBarQss(m_pVscrollBar, 8, 120, 20, "#606060", "#34495E", "#1ABC9C", "#E74C3C");

    //设置列数和列宽


    int width = qApp->desktop()->availableGeometry().width() - 120;
    m_pTableWidget->setColumnCount(5);
    m_pTableWidget->setColumnWidth(0, width * 0.06);
    m_pTableWidget->setColumnWidth(1, width * 0.10);
    m_pTableWidget->setColumnWidth(2, width * 0.06);
    m_pTableWidget->setColumnWidth(3, width * 0.10);
    m_pTableWidget->setColumnWidth(4, width * 0.20);
    m_pTableWidget->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "设备编号" << "设备名称" << "设备地址" << "告警内容" << "告警时间";
    m_pTableWidget->setHorizontalHeaderLabels(headText);
    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget->setAlternatingRowColors(true);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    m_pTableWidget->setRowCount(300);

    for (int i = 0; i < 300; i++) {
        m_pTableWidget->setRowHeight(i, 24);

        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        m_pTableWidget->setItem(i, 0, itemDeviceID);
        m_pTableWidget->setItem(i, 1, itemDeviceName);
        m_pTableWidget->setItem(i, 2, itemDeviceAddr);
        m_pTableWidget->setItem(i, 3, itemContent);
        m_pTableWidget->setItem(i, 4, itemTime);
    }
}
