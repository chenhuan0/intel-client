#include "mainwindow.h"
#include "controlbar.h"
#include "class.h"

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

    //connect(ui.playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui.browseButton, SIGNAL(clicked()), this, SLOT(browse()));
}

void CMainWindow::browse()
{
    
}
void CMainWindow::play(QString& filename)
{
    controlBar = new CControlBar();
    controlBar->show();
    QProcess* process = new QProcess(this);
    QStringList args;
    args << "-slave";
    args << "-quiet";
    args << "-vo";
    args << "fbdev";
    args << "-framedrop";
    args << filename;

    process->start("/mplayer/MPlayer-1.0rc2/mplayer", args);
}