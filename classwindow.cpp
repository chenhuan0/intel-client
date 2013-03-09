#include "classwindow.h"
#include "config.h"
#include "sql.h"

CClassWindow::CClassWindow(QWidget* parent, Qt::WFlags flags)
{
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);
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
    setupButtons();
    connect(ui.backButton, SIGNAL(clicked()), parent, SLOT(browseend()));
    connect(ui.nextButton, SIGNAL(clicked()), this, SLOT(addPages()));
    connect(ui.nextButton, SIGNAL(clicked()), this, SLOT(setupButtons()));
    connect(ui.previousButton, SIGNAL(clicked()), this, SLOT(subPages()));
    connect(ui.previousButton, SIGNAL(clicked()), this, SLOT(setupButtons()));
}
void  CClassWindow::setupButtons()
{

    QToolButton* everyone;
    foreach (everyone, classButtonlist)
    {
        everyone->setFont(QFont(("KaiTi"), 28));
    }
    if (CConfig::NOW_PAGE == MAINCLASS)
    {
        CConfig::getMainClasses();

        //Set the enable stat for previous button and next button
        //According to now page and the total pages
        if (CConfig::PAGE == 0)
        {
            ui.previousButton->setEnabled(false);
        }
        else
        {
            ui.previousButton->setEnabled(true);
        }
        if (CConfig::PAGE == CConfig::result.size() - 1)
        {
            ui.nextButton->setEnabled(false);
        }
        else
        {
            ui.nextButton->setEnabled(true);
        }
        //Display the class in this page
        int count = 0;
        foreach(QToolButton* button, classButtonlist)
        {
            button->setText("NULL");
        }
        foreach(QStringList line, CConfig::result[CConfig::PAGE])
        {
            classButtonlist[count]->setText(line[1]);
            classButtonlist[count]->setVisible(true);
            count++;
        }  
        foreach(QToolButton* button, classButtonlist)
        {
            if (button->text() == "NULL")
            {
                button->setVisible(false);
            }
        }
    }
}

void CClassWindow::addPages()
{
    CConfig::PAGE++;
}

void CClassWindow::subPages()
{
    CConfig::PAGE--;
}
    