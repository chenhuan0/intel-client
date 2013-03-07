#ifndef _CLASS_H_
#define _CLASS_H_ 
#include "common.h"

class PicButton : public QLabel
{
    Q_OBJECT
public:
    PicButton(QWidget* parent = 0) {};
    void setImgs(QPixmap& img1, QPixmap& img2);
    ~PicButton() {};
private:
    QPixmap pressedIMG;
    QPixmap releasedIMG;
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
signals:
    void clicked();
};
#endif
