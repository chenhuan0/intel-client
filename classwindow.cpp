#include "classwindow.h"

CClassWindow::CClassWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);
    setupButtons();
    connect(ui.backButton, SIGNAL(clicked()), parent, SLOT(browseend()));
}
void  CClassWindow::setupButtons()
{
    classButtonlist.append(ui.class1);
    classButtonlist.append(ui.class2);
    classButtonlist.append(ui.class3);
    classButtonlist.append(ui.class4);
    classButtonlist.append(ui.class5);
    classButtonlist.append(ui.class6);
    classButtonlist.append(ui.class7);
    classButtonlist.append(ui.class8);
    classButtonlist.append(ui.class9);
    classButtonlist.append(ui.class10);
    classButtonlist.append(ui.class11);
    classButtonlist.append(ui.class12);

    QToolButton* everyone;
    foreach (everyone, classButtonlist)
    {
        everyone->setFont(QFont(("KaiTi"), 24));
    }
}

    