#ifndef _CLASS_H_
#define _CLASS_H_ 
#include "common.h"

class CPlayController;
class CSlider : public QSlider
{
    Q_OBJECT 
public:
    CSlider(QWidget * parent = 0 );
protected:
    void mouseReleaseEvent ( QMouseEvent * event ) ;
signals:
    void clicked();
};

class MyProxyStyle : public QProxyStyle
{
public:
    int styleHint(StyleHint hint, const QStyleOption *option = 0,
                  const QWidget *widget = 0, QStyleHintReturn *returnData = 0) const
    {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
            return (Qt::LeftButton | Qt::MidButton | Qt::RightButton);
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

class CVideo
{
public:
    QString mainClass;
    QString subClass;
    QString id;
    CVideo(QString main, QString sub, QString content) { mainClass = main; subClass = sub; id = content;};
};
#endif
