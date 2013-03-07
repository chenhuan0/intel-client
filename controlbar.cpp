#include "common.h"
#include "controlbar.h"

CControlBar::CControlBar(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    setMaximumSize(80, 480);
    setMinimumSize(80, 480);
    setGeometry(640, 0, 80, 480);
}