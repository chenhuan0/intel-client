#include "classwindow.h"

CClassWindow::CClassWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);

    connect(ui.backButton, SIGNAL(clicked()), parent, SLOT(browseend()));
}