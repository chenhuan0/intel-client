#ifndef _CLASSWINDOW_H_
#define _CLASSWINDOW_H_
#include "common.h"
#include "config.h"
#include "ui_classwindow.h"

class CClassWindow : public QWidget 
{
    Q_OBJECT
private:
    Ui::classWindow ui;
    QWidget* parent;
    
public:
    CClassWindow(QWidget* parent = 0, Qt::WFlags flags = 0);
    QList<QToolButton*> classButtonlist;

private slots:
    
    void addPages() {CConfig::PAGE++;};
    void subPages() {CConfig::PAGE--;};
    void showClasses();

    void mainClassClicked();
    void backToMainClass();
};
#endif