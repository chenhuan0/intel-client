#include "common.h"
#include "config.h"
#include "sql.h"

int CConfig::NEXT_PAGE;
int CConfig::PREVIOUS_PAGE;
int CConfig::NOW_PAGE;
int CConfig::PAGE = 0;
QList< QList<QStringList> > CConfig::result;

void CConfig::getMainClasses()
{
    string cmd = "select * from mainclasses";
    QString sql = String2QString(cmd);
    QList<QStringList> tmp;
    result.clear();
    if (CSQL::query(String2QString(ROOT_PATH + INDEX_DB_NAME), String2QString("select * from mainclasses;")) == ERROR)
    {
        qDebug() << "Cannot connecct database";
    }
    if (CSQL::result.size() <= 12)
    {       
        result.append(CSQL::result);
    } 
    else
    {
        int count = 0;

        foreach(QStringList everyone, CSQL::result)
        {
            count++;
            tmp.append(everyone);
            if (count == 12)
            {
                result.append(tmp);
                tmp.clear();
                count = 0;
            }
        }
    }
    result.append(tmp);
}