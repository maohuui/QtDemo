
//#pragma execution_character_set("utf-8")
//可以指示char的执行字符集是UTF-8编码。

#include <QApplication>
#include <QTextCodec>
#include "lightbuttonwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    LightButtonWidget w;
    w.setWindowTitle("高亮发光按钮");
    w.show();

    return a.exec();
}
