#ifndef DEVICECONTROL_H_
#define DEVICECONTROL_H_

#include <QtCore>
#include <QThread>

#include "Variables.h"
#include "DeviceValues.h"

/*
 * Меня терзают смутные сомнения относительно необходимости сего класса
 * Единственная его функция - вынести пул устройств в отдельную нить
 */

class DevicesPool;

class DeviceControl : public QThread
{
		Q_OBJECT
	
	private:
		DevicesPool *dp;
					
	public:
		DeviceControl(QObject *);
		virtual void run() { wait(TO_BTWCHECKS); };
};

#endif /*DEVICECONTROL_H_*/
