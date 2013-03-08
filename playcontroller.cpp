#include "common.h"
#include "playcontroller.h"

CPlayController::CPlayController(QWidget* parent, Qt::WFlags flags)
{

    ui.setupUi(this);

    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 

    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);

    connect(ui.playButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui.stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui.stopButton, SIGNAL(clicked()), parent, SLOT(stop()));
    setMouseTracking(true);
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
}


void CPlayController::mouseMoveEvent(QMouseEvent* event)
{
    QPoint mouse = event->pos();
    int x = mouse.x();
    int y = mouse.y();
    if (x <= 640)
    {
        QPoint pos(640, y);
        QCursor::setPos(pos);
    }
}