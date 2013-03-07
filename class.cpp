#include "common.h"
#include "class.h"

void PicButton::setImgs(QPixmap& img1, QPixmap& img2)
{
    releasedIMG = img1;
    pressedIMG = img2;
    setPixmap(img1);
}
void PicButton::mousePressEvent(QMouseEvent* event)
{
    setPixmap(pressedIMG);
}

void PicButton::mouseReleaseEvent(QMouseEvent* event)
{
    setPixmap(releasedIMG);
    emit clicked();
}
