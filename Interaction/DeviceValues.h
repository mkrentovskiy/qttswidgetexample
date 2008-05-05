#ifndef DEVICEVALUES_H_
#define DEVICEVALUES_H_

#include <QtCore>

#include <Variables.h>

/*
 * 	Класс структурного типа. Разумеется, правильнее бы сделать структуру
 *  но, боюсь, ее не так просто будет таскать между тредами
 */

class DeviceValues
{	
	public:
		DeviceState s;
		Speed sp;
		Height h;
	
		DeviceValues();
		DeviceValues(QByteArray);
		
		virtual void operator=(const DeviceValues&);
		virtual bool operator==(const DeviceValues&);
};

#endif /*DEVICEVALUES_H_*/
