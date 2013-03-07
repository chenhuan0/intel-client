#include "mainwindow.h"
#include "class.h"

CMainWindow::CMainWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    this->setup();
    
}

void CMainWindow::setup()
{
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);
    QPixmap playPixmap("images/play.png");
    QPixmap playPressPixmap("images/play-pressed.png");
    ui.playButton->setImgs(playPixmap, playPressPixmap);
    ui.playButton->setAlignment(Qt::AlignCenter);
    ui.playButton->setMinimumSize(playPixmap.size());
    ui.playButton->setMaximumSize(playPixmap.size());

}