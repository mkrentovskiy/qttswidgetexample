#include "DeviceValues.h"

DeviceValues::DeviceValues()
{
	s = DS_NONE;
	h = 0;
}

DeviceValues::DeviceValues(QByteArray ba) 
{
	DeviceValues::DeviceValues();
	
}

void DeviceValues::operator=(const DeviceValues& a)
{
	s = a.s;
	h = a.h;
}

bool DeviceValues::operator==(const DeviceValues& a)
{
	if(s != a.s || h != a.h) return false;
	else return true;
}

