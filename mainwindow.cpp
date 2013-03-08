#include "mainwindow.h"
#include "class.h"
#include "playcontroller.h"
#include "classwindow.h"

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
    this->hide();
    classWindow = new CClassWindow(this);
    classWindow->show();
}

void CMainWindow::browseend()
{
    delete classWindow;
    this->show();
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
