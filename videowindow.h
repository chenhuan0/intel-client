#ifndef _VIDEOWINDOW_H_
#define _VIDEOWINDOW_H_
#include "common.h"
#include "ui_videowindow.h"
#include "config.h"

class CPlayController;
class CVideoWindow : public QWidget 
{
    Q_OBJECT
private:
    Ui::videoWindow ui;
    QWidget* parent;
    CPlayController* playController;

public:
    CVideoWindow(QWidget* parent = 0, Qt::WFlags flags = 0);
    QList<QToolButton*> videoButtonlist;
    QList<QLabel*> interestLabelList;
    QList<QLabel*> haveLabelList;
    QList<QVBoxLayout*> videoLayoutList;

public slots:
    void playstop();
private slots:
    void addPages() {CConfig::PAGE++;};
    void subPages() {CConfig::PAGE--;};
    void showVideos();

    void play();
    void choose();
};
#endif