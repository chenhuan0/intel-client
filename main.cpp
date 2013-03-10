#include "mainwindow.h"
#include "common.h"
#include "config.h"
#include "class.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    CMainWindow w;
    w.show();
    CConfig::NOW_PAGE = START;
    CConfig::NEXT_PAGE = MAINCLASS;
    CConfig::PREVIOUS_PAGE = NO;

    a.setStyle(new MyProxyStyle);
    //Load user interst video
    ifstream interest((ROOT_PATH + INTEREST_FILE).c_str());
    string line;
    while (getline(interest, line))
    {
        CConfig::interestFile.insert(String2QString(line));
    }
    interest.close();
    //Load in device load
    ifstream indevice((ROOT_PATH + HAVE_FILE).c_str());
    while (getline(indevice, line))
    {
        QString info = String2QString(line);
        QString mainclass = info.split("###")[0];
        QString subclass = info.split("###")[1];
        QString content = info.split("###")[2];
        CConfig::haveMainClass.insert(mainclass);
        CConfig::haveSubClass.insert(subclass);
        CConfig::haveFile.insert(content);
    }
    indevice.close();

    return a.exec();
}
