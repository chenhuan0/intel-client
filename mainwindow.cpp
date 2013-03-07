#include "mainwindow.h"
#include "class.h"

CMainWindow::CMainWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    this->setup();
    setMouseTracking(true);
    ui.playButton->setMouseTracking(true);
}

void CMainWindow::setup()
{
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);
}