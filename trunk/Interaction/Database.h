#ifndef DATABASE_H_
#define DATABASE_H_

#include <QObject>
#include <QString>
#include <QString>
#include <QDomDocument>
#include <QFile>

#include <QSqlDatabase>
#include <QSqlQuery>

class Database  : public QObject
{
		Q_OBJECT

	private:
		QSqlDatabase db;
		bool enable;	
				
	public:		
		Database();
		virtual ~Database();

		QSqlQuery query(QString );
};

#endif /*DATABASE_H_*/
