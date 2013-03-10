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
    setGeometry(0, 0, 720, 576);
    connect(ui.playButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui.stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui.stopButton, SIGNAL(clicked()), parent, SLOT(playstop()));
    connect(ui.forwardButton, SIGNAL(clicked()), this, SLOT(forward()));
    connect(ui.backwardButton, SIGNAL(clicked()), this, SLOT(backward()));
    connect(ui.soundButton, SIGNAL(clicked()), this, SLOT(mute()));
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
    args << "720";
    args << "-y";
    args << "480";
    args << filename;
    //mplayer->start("/usr/bin/mplayer", args);
    mplayer->start("/mplayer/MPlayer-1.0rc2/mplayer", args);
    isPlaying = true;
    isMute = false;
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

void CPlayController::mute()
{
    if (isMute)
    {
        mplayer->write("mute 1\n");
        isMute = false;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-sound.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.soundButton->setIcon(icon);
    }
    else
    {
        mplayer->write("mute 0\n");
        isMute = true;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-mute.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.soundButton->setIcon(icon);
    }
}

void CPlayController::mouseMoveEvent(QMouseEvent* event)
{
    QPoint mouse = event->pos();
    int x = mouse.x();
    int y = mouse.y();
    
    if (y <= 490)
    {
        QPoint pos(x, 490);
        QCursor::setPos(pos);
    }
}