#include "mainwindow.h"

CMainWindow::CMainWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("white"));
    setPalette(plt);
}