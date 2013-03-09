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
    this->setup();
}

void CMainWindow::setup()
{
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);

    connect(ui.playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui.browseButton, SIGNAL(clicked()), this, SLOT(browse()));
}

void CMainWindow::browse()
{
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
    playController = new CPlayController(this);
    playController->show();
    playController->setFilename("/home/ch/videos/test.mp4");
    playController->play();
    this->hide();
}

void CMainWindow::playstop()
{
    this->show();
    delete playController;
}
