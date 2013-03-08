#include "common.h"
#include "playcontroller.h"

CPlayController::CPlayController(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    setMaximumSize(80, 480);
    setMinimumSize(80, 480);
    setGeometry(640, 0, 80, 480);
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);

    connect(ui.playButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui.stopButton, SIGNAL(clicked()), this, SLOT(stop()));
}

void CPlayController::play()
{
    mplayer = new QProcess();
    QStringList args;
    args << "-slave";
    args << "-quiet";
    args << "-vo";
    args << "fbdev";
    args << "-framedrop";
    args << "-zoom";
    args << "-x";
    args << "640";
    args << "-y";
    args << "480";
    args << filename;
    //mplayer->start("/usr/bin/mplayer", args);
    mplayer->start("/mplayer/MPlayer-1.0rc2/mplayer", args);
    isPlaying = true;
}


void CPlayController::pause()
{
    mplayer->write("pause\n");
    if (isPlaying)
    {
        isPlaying = false;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-play.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.playButton->setIcon(icon);
    }
    else
    {
        isPlaying = true;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.playButton->setIcon(icon);
    }
}

void CPlayController::stop()
{
    mplayer->terminate();
    delete mplayer;
    delete this;
}