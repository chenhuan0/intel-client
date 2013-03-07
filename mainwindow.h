#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include "common.h"
#include "ui_mainwindow.h"
class PicButton;

class CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    CMainWindow(QWidget* parent = 0, Qt::WFlags flags = 0);

private:
    Ui::mainWindow ui;
    void setup();

private slots:
    void play();
};
#endif 
