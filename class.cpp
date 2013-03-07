#include "common.h"
#include "class.h"

void PicButton::setImgs(QPixmap& img1, QPixmap& img2, QPixmap& img3)
{
    releasedIMG = img1;
    pressedIMG = img2;
    moveIMG = img3;
    setPixmap(img1);
}
void PicButton::mousePressEvent(QMouseEvent* event)
{
    setPixmap(pressedIMG);
    qDebug() << event->pos();
    qDebug() << this->rect();
}
void PicButton::mouseMoveEvent(QMouseEvent* event)
{
    QPoint mouseCursor = event->pos(); 
    QRect connectButtonRect = this->rect(); 
    if (connectButtonRect.contains(mouseCursor) == true) 
    { 
        setPixmap(moveIMG);
    } 
    else
    {
        setPixmap(releasedIMG);
    }
   
}

void PicButton::mouseReleaseEvent(QMouseEvent* event)
{
    setPixmap(releasedIMG);
    emit clicked();
}
