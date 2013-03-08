#ifndef _CONTROLBAR_H_
#define _CONTROLBAR_H_
#include "common.h"
#include "ui_playcontroller.h"

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

    bool isPlaying;
    void mouseMoveEvent(QMouseEvent* event);

private slots:
    void pause();
    void stop();
};
#endif 
