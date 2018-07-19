#ifndef CommandHandler_h
#define CommandHandler_h

#define MAX_IMPLEMENTATIONS 2
#define COMMAND_ID_LENGTH 3

#include <Logger.h>
#include <FlowControl.h>
#include <AbstractCommand.h>
#include <Arduino.h>

class CommandHandler
{
public:
	CommandHandler(Logger& logger, FlowControl& flowControl, byte maxImplementations = MAX_IMPLEMENTATIONS);

	void addCommandImplementation(AbstractCommand& commandImpl);

	void handleCommand(String& input);

private:
	Logger& logger;
	FlowControl& flowControl;

	// Implementation of the commands
	AbstractCommand** commandImplList;
	byte commandImplCounter = 0;
	byte maxCommandImpl;

	// ---- Command handling related methods ----
	// Validates the command ID. Preconditions of true return value:
	// - Non empty String (NULL or zero length)
	// - The input length must be at least COMMAND_ID_LENGTH + 2 (command ID + space + at least one char for paraemter)
	// - Command ID must consist of upper case letters
	// - There must be a space character after the command ID
	bool validateCommandId(String& input);
	// Returns the command ID from a full command input from user or empty String in case of invalid command ID
	String getCommandId(String& input);
};

#endif
