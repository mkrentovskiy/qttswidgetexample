#include <QtSql>

#include "DevicesPool.h"
#include "DeviceControl.h"
#include "Database.h"

#include "Variables.h"

DevicesPool::DevicesPool(QObject *parent, QObject *agent) : QObject(parent)
{
	Database db;
	QSqlQuery q = db.query("SELECT * FROM devices");

	while(q.next()) {
		Device *d = new Device(q.value(_D_id).toString(),
			q.value(_D_ip).toString(),
			q.value(_D_port).toInt());
		
		qRegisterMetaType<DeviceValues>("DeviceValues");
		connect(d, SIGNAL(stateChanged(QString , DeviceValues)), agent, SLOT(deviceStateChanged(QString, DeviceValues)));
		connect(agent, SIGNAL(isNewCommand(QString, int, float)), this, SLOT(sendCommand(QString, int, float)));
		
		devices[(q.value(_D_id).toString())] = d;
	}
}

DevicesPool::~DevicesPool()
{
	QHash<QString, Device *>::iterator i = devices.begin();
 	while (i != devices.end()) {
    	delete i.value();
    	++i;
 	}
 	devices.clear();
}

/*
 * 	Ловим команды и отдаем их устройствам
 * 	Ежели у нас групповые комманды - применяем особую стратегию ;)
 */
void DevicesPool::sendCommand(QString did, int f, float v)
{
	if(did.size() > 1) {
		devices[did]->sendCommand(f, v, 0);
	} else {
		QHash<QString, Device *>::iterator i = devices.begin();
 		while (i != devices.end()) {
    		((Device *) i.value())->sendCommand(f, v, 0);
    		++i;
 		}	
	}
}

void DevicesPool::sendCommand(QString did, int f, float v, float h)
{
	devices[did]->sendCommand(f, v, h);
}
