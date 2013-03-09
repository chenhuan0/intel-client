#include "classwindow.h"
#include "config.h"
#include "sql.h"

CClassWindow::CClassWindow(QWidget* parent, Qt::WFlags flags)
{
    this->parent = parent;
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

    
    connect(ui.nextButton, SIGNAL(clicked()), this, SLOT(addPages()));
    connect(ui.nextButton, SIGNAL(clicked()), this, SLOT(showClasses()));
    connect(ui.previousButton, SIGNAL(clicked()), this, SLOT(subPages()));
    connect(ui.previousButton, SIGNAL(clicked()), this, SLOT(showClasses()));
    
    CConfig::PAGE = 0;
    showClasses();  
}
void  CClassWindow::showClasses()
{
    QToolButton* everyone;
    foreach (everyone, classButtonlist)
    {
        everyone->setFont(QFont(("KaiTi"), 28));
    }
    if (CConfig::NOW_PAGE == MAINCLASS)
    {      
        CConfig::getMainClasses();
        foreach (QToolButton* everyone, classButtonlist)
        {
            connect(everyone, SIGNAL(clicked()), this, SLOT(mainClassClicked()));
            connect(everyone, SIGNAL(clicked()), this, SLOT(showClasses()));
        }
        connect(ui.backButton, SIGNAL(clicked()), parent, SLOT(browseend()));
    }
    else if (CConfig::NOW_PAGE == SUBCLASS)
    {
        CConfig::getSubClasses();
        foreach (QToolButton* everyone, classButtonlist)
        {
            disconnect(everyone, SIGNAL(clicked()), this, SLOT(mainClassClicked()));
            disconnect(everyone, SIGNAL(clicked()), this, SLOT(showClasses()));
        }
        disconnect(ui.backButton, SIGNAL(clicked()), parent, SLOT(browseend()));
        connect(ui.backButton, SIGNAL(clicked()), this, SLOT(backToMainClass()));
    }

    //Set the enable stat for previous button and next button
    //According to now page and the total pages
    if (CConfig::PAGE == 0)
    {
        ui.previousButton->setVisible(false);
    }
    else
    {
        ui.previousButton->setVisible(true);
    }
    if (CConfig::PAGE == CConfig::result.size() - 1)
    {
        ui.nextButton->setVisible(false);
    }
    else
    {
        ui.nextButton->setVisible(true);
    }
    //Display the class in this page
    int count = 0;
    foreach(QToolButton* button, classButtonlist)
    {
        button->setText("NULL");
        button->setAccessibleName("");
    }
    foreach(QStringList line, CConfig::result[CConfig::PAGE])
    {
        classButtonlist[count]->setWhatsThis(line[0]);
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
    
void CClassWindow::mainClassClicked()
{
    QToolButton* mainclass = (QToolButton*)(sender());
    CConfig::subClassID = mainclass->whatsThis();

    CConfig::NOW_PAGE = SUBCLASS;
    CConfig::NEXT_PAGE = CONTENT;
    CConfig::PREVIOUS_PAGE = MAINCLASS;

    CConfig::PAGE = 0;
}

void CClassWindow::backToMainClass()
{
    CConfig::NOW_PAGE = MAINCLASS;
    CConfig::NEXT_PAGE = SUBCLASS;
    CConfig::PREVIOUS_PAGE = START;

    CConfig::PAGE = 0;

    showClasses();
}