#include "Database.h"

#include "Variables.h"


Database::Database()
{
	enable = false;
	
	QFile file(DATABASE);
	QDomDocument params;
	
	QString errorStr;
    int errorLine;
    int errorColumn;
		
	if (file.open(QFile::ReadOnly | QFile::Text)) {
    
    	if (params.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
    		QDomElement root = params.documentElement();    

   			db = QSqlDatabase::addDatabase(root.firstChildElement("driver").text());
    
    		db.setHostName(root.firstChildElement("server").text());
    		db.setDatabaseName(root.firstChildElement("name").text());
    		db.setUserName(root.firstChildElement("user").text());
    		db.setPassword(root.firstChildElement("password").text());   
    	}        
    } 
	
    enable = db.open();
   
    if(enable) {
    	db.exec("SET NAMES 'utf8'");
    }
}

Database::~Database()
{
	if(enable) db.close();
}

QSqlQuery Database::query(QString q) 
{

	if(enable) {
		return	db.exec(q);
	} else {
		return QSqlQuery(); 
	}
}

