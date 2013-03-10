#ifndef _CONTROLBAR_H_
#define _CONTROLBAR_H_
#include "common.h"
#include "ui_playcontroller.h"

class ImSlider;


class CPlayController : public QWidget
{
    Q_OBJECT
public:
    CPlayController(QWidget* parent = 0, Qt::WFlags flags = 0);
    void play();
    void setFilename(QString filename) { this->filename = filename;};
private:
    Ui::playController ui;
    QProcess* mplayer;
    QString filename;
    QWidget* parent;

    bool isPlaying;
    bool isMute;
    bool needGetPos;
    void mouseMoveEvent(QMouseEvent* event);
    float totalTime;
    float nowTime;


private slots:
    void pause();
    void stop();
    
    void forward() { mplayer->write("seek 5\n"); };
    void backward() { mplayer->write("seek -5\n"); };
    void mute();
    void soundIncrease();
    void soundDecrease();

    void message_slots();

    void startDrag();
    void dragging();
    void endDrag();
    void refreshTime();
};



#endif 
