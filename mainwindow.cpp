#include "mainwindow.h"
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

    connect(ui.playButton, SIGNAL(clicked()), this, SLOT(play()));
}

void CMainWindow::play()
{
    QProcess* process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start("/mplayer/MPlayer-1.0rc2/mplayer -framedrop -slave -quiet -vo fbdev ./videos/test.mp4");
}