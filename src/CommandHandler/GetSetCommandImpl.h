#ifndef GetSetCommandImpl_H
#define GetSetCommandImpl_H

#include <AbstractCommand.h>

#define DRIVER_ID_LENGTH 3
#define DEVICE_ID_LENGTH 2
#define ON_LENGTH 2
#define OFF_LENGTH 3

#define SWITCH_PIN 4

class GetSetCommandImpl: public AbstractCommand
{
public:
	GetSetCommandImpl(Logger& logger, FlowControl& flowControl);

	virtual void processCommand(String& commandId, String& commandParameters) override;
	virtual bool supportsCommand(String& command) override;

private:
	// Name of GET command
	String getGetName();
	// Name of SET command
	String getSetName();
	// ON state
	String getOnState();
	// Off state
	String getOffState();

	// Checking command parameters
	// Format of the get / set parameters:
	// First part: Driver ID - 3 uppercase digit selecting the driver to handle the get / set request
	// Second part: Whitespace - exactly one space character
	// Third part: Device ID - Numerical ID of the specified device - exactly two digit long
	// Fourth part (only SET): Whitespace - exactly one space character
	// Fifth part (only SET): ON / OFF
	bool validateGetParameters(String& getSetParameters);
	bool validateSetParameters(String& getSetParameters);
	bool validateParametersBase(String& getSetParameters);

	// Parts of the GET / SET command
	String getDriverId(String& getSetParameters);
	byte getDeviceId(String& getSetParameters);
	// States: ON = true, OFF = false
	bool getDeviceState(String& getSetParameters);

	void processGet(String& getSetParameters);
	void processSet(String& getSetParameters);
};

#endif
