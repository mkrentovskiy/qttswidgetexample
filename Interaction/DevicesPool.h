#ifndef DEVICESPOOL_H_
#define DEVICESPOOL_H_

#include <QtCore>
#include <QHash>

#include "Device.h"

#include "Variables.h"

class DevicesPool : public QObject
{
		Q_OBJECT
	
	private:
		QHash<QString, Device *> devices;

	public slots:
		void sendCommand(QString, int, float);
		void sendCommand(QString, int, float, float);
				
	public:
		DevicesPool(QObject *, QObject *);
		virtual ~DevicesPool();
		
		bool isInPool(QString id) { return devices.contains(id); };
};

#endif /*DEVICESPOOL_H_*/
