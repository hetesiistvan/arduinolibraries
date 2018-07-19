#ifndef AbstractCommand_h
#define AbstractCommand_h

#include <Arduino.h>
#include <FlowControl.h>

class AbstractCommand: public FlowControl
{
public:
	// Processes a command
	// Parameter should contain the command parameters from the user (after the command ID and the proceeding space)
	virtual void processCommand(String& command) = 0;
	// Checks if a command is supported by that specific implementation or not
	// Parameter should contain only the command ID
	virtual bool supportsCommand(String& command) = 0;
	// Sets up a flow control instance (this is being inherited from the command handler)
	virtual void setFlowControl(FlowControl& flowControl) = 0;
};

#endif
