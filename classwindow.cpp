#include "classwindow.h"
#include "videowindow.h"
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
    setGeometry(0, 0, 720, 576);
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
        QFont font("KaiTi", 28);
        font.setBold(true);
        everyone->setFont(font);
    }
    if (CConfig::NOW_PAGE == MAINCLASS)
    {      
        CConfig::getMainClasses();
        foreach (QToolButton* everyone, classButtonlist)
        {
            disconnect(everyone, SIGNAL(clicked()), this, SLOT(subClassClicked()));
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
            connect(everyone, SIGNAL(clicked()), this, SLOT(subClassClicked()));
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
        button->setWhatsThis("");
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
    CConfig::mainClassID = mainclass->whatsThis();

    CConfig::NOW_PAGE = SUBCLASS;
    CConfig::NEXT_PAGE = CONTENT;
    CConfig::PREVIOUS_PAGE = MAINCLASS;

    CConfig::PAGE = 0;
}

void CClassWindow::subClassClicked()
{
    QToolButton* subclass = (QToolButton*)(sender());
    CConfig::subClassID = subclass->whatsThis();

    CConfig::NOW_PAGE = CONTENT;
    CConfig::NEXT_PAGE = NO;
    CConfig::PREVIOUS_PAGE = SUBCLASS;

    CConfig::PAGE = 0;

    this->hide();
    videoWindow = new CVideoWindow(this);
    videoWindow->show();
}

void CClassWindow::backToMainClass()
{
    CConfig::NOW_PAGE = MAINCLASS;
    CConfig::NEXT_PAGE = SUBCLASS;
    CConfig::PREVIOUS_PAGE = START;

    CConfig::PAGE = 0;
    showClasses();
}

void CClassWindow::backFromContent()
{
    CConfig::NOW_PAGE = SUBCLASS;
    CConfig::NEXT_PAGE = CONTENT;
    CConfig::PREVIOUS_PAGE = MAINCLASS;

    CConfig::PAGE = 0;

    this->show();  
    delete videoWindow;
    //Write interest set to file
    ofstream interest((ROOT_PATH + INTEREST_FILE).c_str());
    foreach (QString each, CConfig::interestFile)
    {
        interest << QString2String(each) << endl;
    }
    interest.close();

    ofstream del((ROOT_PATH + DEL_FILE).c_str());
    foreach (QString each, CConfig::wantDelFile)
    {
        del << QString2String(each) << endl;
    }
    del.close();

    system("sync");
}