#include "common.h"
#include "sql.h"

QString CSQL::lastError;
QList<QStringList> CSQL::result;
QSqlDatabase CSQL::db = QSqlDatabase::addDatabase("QSQLITE"); 
BOOL CSQL::query(QString dbname, QString sql)
{
	result.clear();
	db.setDatabaseName(dbname); 
	if (!db.open())
	{
		lastError = tr("Failed to open database.");
		return ERROR;
	}
	QSqlQuery query;
	if (query.exec(sql))
	{
		int columns = query.record().count();
		while (query.next())
		{
			QStringList tmp;
			int i;
			for (i = 0; i < columns; i++)
			{
				tmp << query.value(i).toString();
			}
			result << tmp;
		}
	}
	else
	{
		lastError = tr("Failed to query database.");
		return ERROR;
	}
	db.close();
	return SUCCESS;
}