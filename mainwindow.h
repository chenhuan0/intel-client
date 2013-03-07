#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include "common.h"
#include "ui_mainwindow.h"

class CControlBar;
class CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    CMainWindow(QWidget* parent = 0, Qt::WFlags flags = 0);

private:
    Ui::mainWindow ui;
    CControlBar* controlBar;
    void setup();

private slots:
    void play(QString& filename);
    void browse();
};
#endif 
