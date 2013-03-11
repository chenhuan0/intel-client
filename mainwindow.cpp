#include "mainwindow.h"
#include "class.h"
#include "playcontroller.h"
#include "classwindow.h"
#include "config.h"

CMainWindow::CMainWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    setGeometry(0, 0, 720, 576);
    this->setup();
}

void CMainWindow::setup()
{
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);

    connect(ui.playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui.browseButton, SIGNAL(clicked()), this, SLOT(browse()));
    connect(ui.powerButton, SIGNAL(clicked()), this, SLOT(power()));
}

void CMainWindow::browse()
{
    CConfig::isPlay = false;
    CConfig::NOW_PAGE = MAINCLASS;
    CConfig::NEXT_PAGE = SUBCLASS;
    CConfig::PREVIOUS_PAGE = START;
    this->hide();
    classWindow = new CClassWindow(this);
    classWindow->show();
}

void CMainWindow::browseend()
{
    delete classWindow;
    this->show();
    CConfig::NOW_PAGE = START;
    CConfig::NEXT_PAGE = MAINCLASS;
    CConfig::PREVIOUS_PAGE = NO;
}
void CMainWindow::play()
{
    CConfig::isPlay = true;
    CConfig::NOW_PAGE = MAINCLASS;
    CConfig::NEXT_PAGE = SUBCLASS;
    CConfig::PREVIOUS_PAGE = START;
    this->hide();
    classWindow = new CClassWindow(this);
    classWindow->show();
}

void CMainWindow::power()
{
    system("init 0");
}