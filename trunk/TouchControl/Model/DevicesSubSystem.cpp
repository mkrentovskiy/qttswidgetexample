#include <QtCore>
#include <QtSql>

#include "DevicesSubSystem.h"
#include "../View/WidgetControl.h"

#include "../Variables.h"

#ifdef DEBUG
	#include <iostream.h>
#endif

DevicesSubSystem::DevicesSubSystem()
{
	Database db;
	QSqlQuery q = db.query("SELECT * FROM devices");

	while(q.next()) {
		DeviceLimits dl;
		bool ok;
		
		dl.maxv = (float) q.value(_D_maxv).toDouble(&ok);
		dl.minh = (float) q.value(_D_minh).toDouble(&ok);
		dl.maxh = (float) q.value(_D_maxh).toDouble(&ok);
		dl.h = (float) q.value(_D_is_h).toBool();
		
		titles[(q.value(_D_id).toString())] = q.value(_D_title).toString();
		limits[(q.value(_D_id).toString())] = dl;

		#ifdef DEBUG
			cout << "Devices: " << q.value(_D_id).toString().toStdString() << endl;
		#endif
	}
	
}

void DevicesSubSystem::init(WidgetControl *wci)
{
	wc = wci;
	dc = new DeviceControl(this);
	dc->run();
}

/*
 * 	Слоты 	
 */

void DevicesSubSystem::deviceStateChanged(QString did, DeviceValues dv)
{
	// wc->deviceStateChanged(did, dv.s, dv.h);
}

/*
 * 	Функции непосредственной задачи управления
 */
 
void DevicesSubSystem::setSpeed(QString did, Speed s)
{
	#ifdef DEBUG
		cout << "Send speed to " << did.toStdString() << " value " << s << endl;
	#endif
	emit isNewCommand(did, C_SPEED, (float) s);
}

void DevicesSubSystem::setMasterSpeed(Speed s)
{
	#ifdef DEBUG
		cout << "Send master speed value " << s << endl;
	#endif
	emit isNewCommand("", C_MASTERSPEED, (float) s);
}

void DevicesSubSystem::setDirection(QString did, Direction d)
{
	#ifdef DEBUG
		cout << "Send direction to " << did.toStdString() << " value " << d << endl;
	#endif
	emit isNewCommand(did, C_DIRECTION, (float) d);
}

void DevicesSubSystem::setHeight(QString did, Height h)
{
	#ifdef DEBUG
		cout << "Send height to " << did.toStdString() << " value " << h << endl;
	#endif
	emit isNewCommand(did, C_HEIGHT, (float) h);
}

void DevicesSubSystem::setStart(QString did)
{
	#ifdef DEBUG
		cout << "Send start to " << did.toStdString() << endl;
	#endif
	emit isNewCommand(did, C_START, 0);
}

void DevicesSubSystem::setStop(QString did)
{
	#ifdef DEBUG
		cout << "Send stop to " << did.toStdString() << endl;
	#endif
	emit isNewCommand(did, C_STOP, 0);
}

void DevicesSubSystem::setTotalStart()
{
	#ifdef DEBUG
		cout << "Send total start" << endl;
	#endif
	emit isNewCommand("", C_TOTALSTART, 0);
}

void DevicesSubSystem::setTotalStop()
{
	#ifdef DEBUG
		cout << "Send total stop" << endl;
	#endif
	emit isNewCommand("", C_TOTALSTOP, 0);
}
