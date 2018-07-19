#ifndef AbstractCommand_h
#define AbstractCommand_h

#include <Arduino.h>
#include <FlowControl.h>
#include <Logger.h>

class AbstractCommand
{
public:
	AbstractCommand(FlowControl& flowControl, Logger& logger);

	// Processes a command
	// Parameter commandId contains the ID of the command
	// Parameter commandParameters hould contain the command parameters from the user
	// (after the command ID and the proceeding space)
	virtual void processCommand(String& commandId, String& commandParameters) = 0;
	// Checks if a command is supported by that specific implementation or not
	// Parameter should contain only the command ID
	virtual bool supportsCommand(String& command) = 0;

protected:
	FlowControl& flowControl;
	Logger& logger;
};

#endif
