#ifndef AbstractDriver_H
#define AbstractDriver_H

#include <Arduino.h>
#include <Logger.h>
#include <FlowControl.h>

class AbstractDriver
{
public:
	AbstractDriver(Logger& logger, FlowControl& flowControl);

	// Decides if the driver supports GET operation or not
	virtual bool supportsGet() = 0;
	// Decides if the driver supports SET operation or not
	virtual bool supportsSet() = 0;

	// GET operation
	virtual void processGet(int deviceId) = 0;
	// SET operation
	// deviceState parameter defines the desired state: true -> ON, false -> OFF
	virtual void processSet(int deviceId, bool deviceState) = 0;

	// Name of the driver (consists of 3 uppercase characters)
	virtual String getDriverName() = 0;

protected:
	FlowControl& flowControl;
	Logger& logger;
};

#endif