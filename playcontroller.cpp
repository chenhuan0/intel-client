#include "common.h"
#include "playcontroller.h"

CPlayController::CPlayController(QWidget* parent, Qt::WFlags flags)
{
    this->parent = parent;
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
    connect(ui.soundIncreaseButton, SIGNAL(clicked()), this, SLOT(soundIncrease()));
    connect(ui.soundDecreaseButton, SIGNAL(clicked()), this, SLOT(soundDecrease()));

    connect(ui.playProgress, SIGNAL(sliderPressed()), this, SLOT(startDrag()));
    connect(ui.playProgress, SIGNAL(sliderMoved(int)), this, SLOT(dragging()));
    connect(ui.playProgress, SIGNAL(sliderReleased()), this, SLOT(endDrag()));
    connect(ui.playProgress, SIGNAL(valueChanged(int)), this, SLOT(refreshTime()));
    connect(ui.playProgress, SIGNAL(clicked()), this, SLOT(seek()));

    
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
    mplayer->start(String2QString(MPLAYER_PATH), args);
    
    isPlaying = true;
    isMute = false;
    connect(mplayer, SIGNAL(readyReadStandardOutput()), this, SLOT(message_slots()));
    connect(mplayer, SIGNAL(finished(int)), parent, SLOT(playstop()));
    mplayer->write("get_time_length\n");
    mplayer->write("get_time_pos\n");
    needGetPos = true;
}

void CPlayController::pause()
{
    mplayer->write("pause\n");
    if (isPlaying)
    {
        isPlaying = false;
        needGetPos = false;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-play.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.playButton->setIcon(icon);
    }
    else
    {
        isPlaying = true;
        needGetPos = true;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.playButton->setIcon(icon);
        mplayer->write("get_time_pos\n");
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
        mplayer->write("mute 0\n");
        isMute = false;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-sound.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.soundButton->setIcon(icon);
    }
    else
    {
        mplayer->write("mute 1\n");
        isMute = true;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-mute.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.soundButton->setIcon(icon);
    }
}

void CPlayController::soundIncrease()
{
    if (isMute)
    {
        mplayer->write("mute 0\n");
        isMute = false;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-sound.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.soundButton->setIcon(icon);
    }
    mplayer->write("volume +1\n");
}

void CPlayController::soundDecrease()
{
    if (isMute)
    {
        mplayer->write("mute 0\n");
        isMute = false;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/control-sound.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui.soundButton->setIcon(icon);
    }
    mplayer->write("volume -1\n");
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

QString convertTime(float oldtime)
{
    int time = int(oldtime);
    int hour, minute, second;
    if (time < 60)
    {
        hour = 0;
        minute = 0;
        second = time;
    }
    else if (time < 3600)
    {
        hour = 0;
        minute = time / 60;
        second = time - minute * 60;
    }
    else
    {
        hour = time / 3600;
        minute = (time - hour * 3600) / 60;
        second = time - hour * 3600 - minute * 60;
    }
    QString result;
    result.sprintf("%02d:%02d:%02d", hour, minute, second);
    return result;
}

void CPlayController::message_slots()
{
    while(mplayer->canReadLine())
    {
        QByteArray buffer(mplayer->readLine());
        if (buffer.startsWith("ANS_LENGTH"))
        {
            buffer.remove(0, 11);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QString string = codec->toUnicode(buffer);
            totalTime =  string.toFloat();
            QString totalTimeStr = convertTime(totalTime);
            ui.totalTime->setText(totalTimeStr);
        }
        if (buffer.startsWith("ANS_TIME_POSITION"))
        {
            buffer.remove(0, 18);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QString string = codec->toUnicode(buffer);
            nowTime = string.toFloat();
            int percent = nowTime / totalTime * 100;
            if (needGetPos)
            {
                ui.playProgress->setValue(percent);
                ui.nowTime->setText(convertTime(nowTime));
                mplayer->write("get_time_pos\n");
            }        
        }
    }
}

void CPlayController::dragging()
{

}

void CPlayController::refreshTime()
{
    int percent = ui.playProgress->value();
    nowTime = totalTime * (percent / 100.0);
    ui.nowTime->setText(convertTime(nowTime));
}

void CPlayController::startDrag()
{
    needGetPos = false;
}

void CPlayController::endDrag()
{
    needGetPos = true;
    mplayer->write("get_time_pos\n");
}

void CPlayController::seek()
{
    needGetPos = false;
    int percent = ui.playProgress->value();
    nowTime = totalTime * (percent / 100.0);
    QString cmd;
    cmd.sprintf("seek %f 2\n", nowTime);
    mplayer->write(QString2String(cmd).c_str());
    needGetPos = true;
}