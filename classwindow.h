#ifndef _CLASSWINDOW_H_
#define _CLASSWINDOW_H_
#include "common.h"
#include "ui_classwindow.h"

class CClassWindow : public QWidget 
{
    Q_OBJECT
private:
    Ui::classWindow ui;
public:
    CClassWindow(QWidget* parent = 0, Qt::WFlags flags = 0);

};
#endif