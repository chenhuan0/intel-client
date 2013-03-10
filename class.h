#ifndef _CLASS_H_
#define _CLASS_H_ 
#include "common.h"

class CSlider : public QSlider
{
    Q_OBJECT 
public:
    CSlider(QWidget * parent = 0 );

protected:
    void mouseReleaseEvent ( QMouseEvent * event ) ;
};
#endif
