#include "mainwindow.h"
#include "class.h"
#include "playcontroller.h"

CMainWindow::CMainWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    this->setup();
    setMouseTracking(true);
    ui.playButton->setMouseTracking(true);
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
    
}
void CMainWindow::play()
{
    playController = new CPlayController(this);
    playController->show();
    playController->setFilename("./test.mkv");
    playController->play();
}