#include "common.h"
#include "class.h"
#include "playcontroller.h"

CSlider::CSlider( QWidget * parent) :QSlider(parent)
{

} 

void CSlider::mouseReleaseEvent ( QMouseEvent * event )
{
    emit(clicked());
    QSlider::mouseReleaseEvent(event);
}