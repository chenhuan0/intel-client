#include "common.h"
#include "config.h"
#include "sql.h"
#include "class.h"

int CConfig::NEXT_PAGE;
int CConfig::PREVIOUS_PAGE;
int CConfig::NOW_PAGE;

int CConfig::PAGE = 0;
bool CConfig::isPlay = true;
QList< QList<QStringList> > CConfig::result;

QString CConfig::subClassID;
QString CConfig::mainClassID;

QSet<QString> CConfig::interestFile;
QSet<QString> CConfig::wantDelFile;
QSet<QString> CConfig::haveFile;
QSet<QString> CConfig::haveMainClass;
QSet<QString> CConfig::haveSubClass;

void CConfig::getMainClasses()
{
    string cmd = "select * from mainclasses";
    QString sql;
    if (CConfig::isPlay)
    {
        QString addin = String2QString(" where id in (");
        QStringList tmpList;
        foreach(QString tmp, CConfig::haveMainClass)
        {
            tmpList << tmp;
        }
        addin = addin + tmpList.join(",") + ")";
        sql = String2QString(cmd) + addin;
    }
    else
    {
        sql = String2QString(cmd);
    }
    QList<QStringList> tmp;
    result.clear();
    if (CSQL::query(String2QString(ROOT_PATH + INDEX_DB_NAME), sql) == ERROR)
    {
        qDebug() << "Cannot connecct database";
    }
    for (int i = 0; i < CSQL::result.size(); i++)
    {
        QStringList everyone = CSQL::result[i];
        QString id = everyone[0];
        int number = 0;
        sql = String2QString("select * from subclasses where mainclass = ");
        sql += id;
        if (CSQL::count(String2QString(ROOT_PATH + INDEX_DB_NAME), sql) == ERROR)
        {
            qDebug() << "Cannot connecct database";
        }
        foreach(QStringList each, CSQL::secondResult)
        {
            if (CConfig::isPlay)
            {
                if (CConfig::haveSubClass.contains(each[0]))
                {
                    number++;
                }
            }
            else
            {
                number++;
            }
        }
        QString numStr;
        numStr.sprintf("(%d)", number);
        CSQL::result[i].append(numStr);
    }
    if (CSQL::result.size() <= CLASS_MAXDISPLAY)
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
            if (count == CLASS_MAXDISPLAY)
            {
                result.append(tmp);
                tmp.clear();
                count = 0;
            }
        }
    }
    if (!tmp.empty())
    {
        result.append(tmp);
    }
}

void CConfig::getSubClasses()
{
    string cmd = "select * from subclasses where mainclass = ";
    QString sql;
    if (CConfig::isPlay)
    {
        QString addin = String2QString(" and id in (");
        QStringList tmpList;
        foreach(QString tmp, CConfig::haveSubClass)
        {
            tmpList << tmp;
        }
        addin = addin + tmpList.join(",") + ")";
        sql = String2QString(cmd) + mainClassID + addin;
    }
    else
    {
        sql = String2QString(cmd) + mainClassID;
    }

    QList<QStringList> tmp;
    result.clear();
    if (CSQL::query(String2QString(ROOT_PATH + INDEX_DB_NAME), sql) == ERROR)
    {
        qDebug() << "Cannot connecct database";
    }

    for (int i = 0; i < CSQL::result.size(); i++)
    {
        QStringList everyone = CSQL::result[i];
        QString id = everyone[0];
        int number = 0;
        sql = String2QString("select * from contents where subclass = ");
        sql += id;
        if (CSQL::count(String2QString(ROOT_PATH + INDEX_DB_NAME), sql) == ERROR)
        {
            qDebug() << "Cannot connecct database";
        }
        foreach(QStringList each, CSQL::secondResult)
        {
            if (CConfig::isPlay)
            {
                if (CConfig::haveFile.contains(each[0]))
                {
                    number++;
                }
            }
            else
            {
                number++;
            }
        }
        QString numStr;
        numStr.sprintf("(%d)", number);
        CSQL::result[i].append(numStr);
    }

    if (CSQL::result.size() <= CLASS_MAXDISPLAY)
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
            if (count == CLASS_MAXDISPLAY)
            {
                result.append(tmp);
                tmp.clear();
                count = 0;
            }
        }
    }
    if (!tmp.empty())
    {
        result.append(tmp);
    }
}

void CConfig::getVideos()
{
    string cmd = "select * from contents where subclass = ";
    QString sql;

    if (CConfig::isPlay)
    {
        QString addin = String2QString(" and id in ('");
        QStringList tmpList;
        foreach(QString tmp, CConfig::haveFile)
        {
            tmpList << tmp;
        }
        addin = addin + tmpList.join("','") + "')";
        sql = String2QString(cmd) + subClassID + addin;
    }
    else
    {
        sql = String2QString(cmd) + subClassID;
    }
    QList<QStringList> tmp;
    result.clear();
    if (CSQL::query(String2QString(ROOT_PATH + INDEX_DB_NAME), sql) == ERROR)
    {
        qDebug() << "Cannot connecct database";
    }
    if (CSQL::result.size() <= VIDEO_MAXDISPLAY)
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
            if (count == VIDEO_MAXDISPLAY)
            {
                result.append(tmp);
                tmp.clear();
                count = 0;
            }
        }
    }
    if (!tmp.empty())
    {
        result.append(tmp);
    }
}