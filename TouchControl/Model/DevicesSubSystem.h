#ifndef DEVICESSUBSYSTEM_H_
#define DEVICESSUBSYSTEM_H_

#include <QObject>
#include <QHash>

#include "../Variables.h"

#include "../../Interaction/Database.h"
#include "../../Interaction/DeviceControl.h"

class WidgetControl;

class DevicesSubSystem : public QObject
{
		Q_OBJECT
	
	private:
		DeviceControl	*dc;	
		WidgetControl	*wc;
			
		QHash<QString, QString> titles;
		QHash<QString, DeviceLimits> limits;
	
	signals:
		void isNewCommand(QString, int, float);
			
	public slots:
		void deviceStateChanged(QString, DeviceValues);
			
	public:
		DevicesSubSystem();
		
		void init(WidgetControl *);
		
		// Для непосредственного управления
		void setSpeed(QString, Speed);
		void setMasterSpeed(Speed);
		void setDirection(QString, Direction);
		void setHeight(QString, Height);
		void setStart(QString);
		void setStop(QString);
		void setTotalStart();
		void setTotalStop();
		
		// Справочные функции
		bool isInPool(QString did) { return limits.contains(did); };
		QString getTitle(QString did) { return titles[did]; };
		DeviceLimits getLimits(QString did) { return limits[did]; };
};

#endif /*DEVICESSUBSYSTEM_H_*/
