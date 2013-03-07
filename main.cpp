#include "mainwindow.h"
#include "common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    QFont font("wenquanyi", 6);
    a.setFont(font);
    CMainWindow w;
    w.show();
    return a.exec();
}
