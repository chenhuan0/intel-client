#ifndef _CLASS_H_
#define _CLASS_H_ 
#include "common.h"

class PicButton : public QLabel
{
    Q_OBJECT
public:
    PicButton(QWidget* parent = 0) {};
    void setImgs(QPixmap& img1, QPixmap& img2, QPixmap& img3);
    ~PicButton() {};
private:
    QPixmap pressedIMG;
    QPixmap releasedIMG;
    QPixmap moveIMG;
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
signals:
    void clicked();
};
#endif
