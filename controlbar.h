#ifndef _CONTROLBAR_H_
#define _CONTROLBAR_H_
#include "common.h"
#include "ui_controlbar.h"

class CControlBar : public QWidget
{
    Q_OBJECT
public:
    CControlBar(QWidget* parent = 0, Qt::WFlags flags = 0);

private:
    Ui::controlBar ui;
};
#endif 
