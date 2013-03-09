#ifndef _CLASSWINDOW_H_
#define _CLASSWINDOW_H_
#include "common.h"
#include "config.h"
#include "ui_classwindow.h"

class CVideoWindow;

class CClassWindow : public QWidget 
{
    Q_OBJECT
private:
    Ui::classWindow ui;
    QWidget* parent;
    CVideoWindow* videoWindow;

public:
    CClassWindow(QWidget* parent = 0, Qt::WFlags flags = 0);
    QList<QToolButton*> classButtonlist;

private slots:
    
    void addPages() {CConfig::PAGE++;};
    void subPages() {CConfig::PAGE--;};
    void showClasses();

    void mainClassClicked();
    void subClassClicked();

    void backToMainClass();
    void backFromContent();
};
#endif