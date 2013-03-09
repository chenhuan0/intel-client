#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "common.h"

class CConfig : public QObject
{
    Q_OBJECT
public:
    static int NEXT_PAGE;
    static int PREVIOUS_PAGE;
    static int NOW_PAGE;

    static QList< QList<QStringList> > result;

    static int PAGE;
    static void getMainClasses();

    static QString mainClassID;
    static void getSubClasses();

    static QString subClassID;
    static void getVideos();
};

#endif