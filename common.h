#ifndef _COMMON_H_
#define _COMMON_H_
#include <QtGui>
#include <QSqlDatabase> 
#include <QSqlQuery>
#include <QSqlRecord>
#include <iostream>
#include <string>
using namespace std;

const string ROOT_PATH = "./";
const string INDEX_DB_NAME = "indexdb";
const string CONTENT_DB_NAME = "contentdb";

typedef int BOOL;
const int SUCCESS = 1;
const int ERROR = 0;
const QString NO_VALUE = "-1";
const QString CLASS = "0";
const QString CONTENT = "1";

static string QString2String(const QString& s)
{
    return string((const char*)s.toLocal8Bit());
}

static QString String2QString(const string& s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}
#endif
