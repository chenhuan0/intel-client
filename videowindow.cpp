#include "videowindow.h"
#include "config.h"
#include "sql.h"
#include "playcontroller.h"

CVideoWindow::CVideoWindow(QWidget* parent, Qt::WFlags flags)
{
    this->parent = parent;
    ui.setupUi(this);
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags); 
    QPalette plt = palette();
    plt.setColor(QPalette::Background, QColor("black"));
    setPalette(plt);
    setGeometry(0, 0, 720, 576);

    videoButtonlist.append(ui.video_1);
    videoButtonlist.append(ui.video_2);
    videoButtonlist.append(ui.video_3);
    videoButtonlist.append(ui.video_4);
    videoButtonlist.append(ui.video_5);
    videoButtonlist.append(ui.video_6);

    interestLabelList.append(ui.interest_1);
    interestLabelList.append(ui.interest_2);
    interestLabelList.append(ui.interest_3);
    interestLabelList.append(ui.interest_4);
    interestLabelList.append(ui.interest_5);
    interestLabelList.append(ui.interest_6);

    haveLabelList.append(ui.have_1);
    haveLabelList.append(ui.have_2);
    haveLabelList.append(ui.have_3);
    haveLabelList.append(ui.have_4);
    haveLabelList.append(ui.have_5);
    haveLabelList.append(ui.have_6);

    videoLayoutList.append(ui.verticalLayout_1);
    videoLayoutList.append(ui.verticalLayout_2);
    videoLayoutList.append(ui.verticalLayout_3);
    videoLayoutList.append(ui.verticalLayout_4);
    videoLayoutList.append(ui.verticalLayout_5);
    videoLayoutList.append(ui.verticalLayout_6);

    connect(ui.nextButton, SIGNAL(clicked()), this, SLOT(addPages()));
    connect(ui.nextButton, SIGNAL(clicked()), this, SLOT(showVideos()));
    connect(ui.previousButton, SIGNAL(clicked()), this, SLOT(subPages()));
    connect(ui.previousButton, SIGNAL(clicked()), this, SLOT(showVideos()));
    CConfig::PAGE = 0;
    showVideos();  

    connect(ui.backButton, SIGNAL(clicked()), parent, SLOT(backFromContent()));
    foreach (QToolButton* everyone, videoButtonlist)
    {
        QFont font("Microsoft YaHei", 18);
        font.setBold(true);
        everyone->setFont(font);
        if (CConfig::isPlay)
        {
            connect(everyone, SIGNAL(clicked()), this, SLOT(play()));
        }
        else
        {
            connect(everyone, SIGNAL(clicked()), this, SLOT(choose()));
        }
        
    }
    foreach (QLabel* label, interestLabelList)
    {
        QFont font("Microsoft YaHei", 14);
        font.setBold(true);
        label->setFont(font);
    }
    foreach (QLabel* label, haveLabelList)
    {
        QFont font("Microsoft YaHei", 14);
        font.setBold(true);
        label->setFont(font);
    }
}

void CVideoWindow::showVideos()
{
    CConfig::getVideos();

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
    foreach(QToolButton* button, videoButtonlist)
    {
        button->setText("NULL");
        button->setWhatsThis("");
    }
    foreach(QLabel* label, interestLabelList)
    {
        label->setText("");
    }
    foreach(QLabel* label, haveLabelList)
    {
        label->setText("");
    }
    foreach(QStringList line, CConfig::result[CConfig::PAGE])
    {

        videoButtonlist[count]->setWhatsThis(line[0]);
        videoButtonlist[count]->setText(line[1]);
        videoButtonlist[count]->setVisible(true);
        videoButtonlist[count]->setIcon(QIcon(String2QString(ROOT_PATH + "previews/") + line[3]));
        if (!CConfig::isPlay)
        {
            if (CConfig::interestFile.contains(line[0]))
            {
                interestLabelList[count]->setText("感兴趣");
            }
            if (CConfig::haveFile.contains(line[0]))
            {
                haveLabelList[count]->setText("本机有此视频");
            }
        }
        count++;
    }  

    if (CConfig::isPlay)
    {
        foreach(QLabel* label, interestLabelList)
        {
            label->setVisible(false);
        }
        foreach(QLabel* label, haveLabelList)
        {
            label->setVisible(false);
        }
    }
    else
    {
        for (int i = 0; i < videoButtonlist.size(); i++)
        {
            if (videoButtonlist[i]->text() == "NULL")
            {
                videoButtonlist[i]->setVisible(false);
                interestLabelList[i]->setVisible(false);
                haveLabelList[i]->setVisible(false);
            }
        }
    }
}

void CVideoWindow::play()
{
    QToolButton* subclass = (QToolButton*)(sender());
    QString contentID = subclass->whatsThis();
    QString sql = String2QString("select filename from contents where id = ") + contentID;
    if (CSQL::query(String2QString(ROOT_PATH + INDEX_DB_NAME), sql) == ERROR)
    {
        qDebug() << "Cannot connecct database";
    }
    QString filename =CSQL::result[0][0];
    playController = new CPlayController(this);
    playController->show();
    playController->setFilename(String2QString(ROOT_PATH + "videos/") + filename);
    playController->play();
    this->hide();
}

void CVideoWindow::playstop()
{
    this->show();
    delete playController;
}

void CVideoWindow::choose()
{
    QToolButton* subclass = (QToolButton*)(sender());
    QString mainClassID = CConfig::mainClassID;
    QString subClassID = CConfig::subClassID;
    QString contentID = subclass->whatsThis();
    QString name = subclass->text().split("\n")[0];
    int index = subclass->objectName().split("_")[1].toInt() - 1;
    if (CConfig::interestFile.contains(contentID))
    {
        CConfig::interestFile.remove(contentID);
        CConfig::wantDelFile.insert(contentID);
        subclass->setText(name);
        interestLabelList[index]->setText("");
    }
    else
    {
        CConfig::interestFile.insert(contentID);
        CConfig::wantDelFile.remove(contentID);
        interestLabelList[index]->setText("感兴趣");
    }
}