#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include "common.h"
#include "ui_mainwindow.h"

class CPlayController;
class CClassWindow;

class CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    CMainWindow(QWidget* parent = 0, Qt::WFlags flags = 0);

private:
    Ui::mainWindow ui;
    CPlayController* playController;
    CClassWindow* classWindow;
    void setup();


public slots:
    void playstop();
    void browseend();
private slots:
    void play();
    void browse();
};
#endif 
