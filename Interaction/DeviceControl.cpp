#include "DeviceControl.h"
#include "DevicesPool.h"

DeviceControl::DeviceControl(QObject *agent)
{
	dp = new DevicesPool(this, agent);
}
