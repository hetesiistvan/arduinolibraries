#ifndef AbstractCommand_h
#define AbstractCommand_h

#include <Arduino.h>
#include <FlowControl.h>

class AbstractCommand: public FlowControl
{
public:
	// Processes a command
	// Parameter should contain the full command input from the user
	virtual void processCommand(String& command) = 0;
	// Checks if a command is supported by that specific implementation or not
	// Parameter should contain the full command input from the user
	virtual bool supportsCommand(String& command) = 0;
	// Sets up a flow control instance (this is being inherited from the command handler)
	virtual void setFlowControl(FlowControl& flowControl) = 0;
};

#endif
