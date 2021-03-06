#ifndef _SQL_H_
#define _SQL_H_
#include "common.h"

class CSQL : public QObject
{
	Q_OBJECT
public:
	static BOOL query(QString dbname, QString sql);
    static BOOL count(QString dbname, QString sql);
	static BOOL modify(QString& dbname, QString& sql);
	static QString lastError;
	static QList<QStringList> result;
    static QList<QStringList> secondResult;
    static QString num;
private:
	static QSqlDatabase db;
};
#endif