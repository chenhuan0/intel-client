#include "mainwindow.h"
#include "common.h"
#include "config.h"

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
    CConfig::NOW_PAGE = START;
    CConfig::NEXT_PAGE = MAINCLASS;
    CConfig::PREVIOUS_PAGE = NO;
    //Load user interst video
    ifstream interest((ROOT_PATH + INTEREST_FILE).c_str());
    string line;
    while (getline(interest, line))
    {
        CConfig::interestFile.insert(String2QString(line));
    }
    return a.exec();
}
