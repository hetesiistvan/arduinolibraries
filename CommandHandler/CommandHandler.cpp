#include <CommandHandler.h>

CommandHandler::CommandHandler(Logger& logger, FlowControl& flowControl, byte maxImplementations)
	: logger(logger), flowControl(flowControl), maxCommandImpl(maxImplementations) {
	commandImplList = new AbstractCommand*[maxImplementations];
}

void CommandHandler::addCommandImplementation(AbstractCommand& commandImpl) {
	if (commandImplCounter +1 <= maxCommandImpl) {
		commandImplList[commandImplCounter] = &commandImpl;
		commandImplCounter++;
		logger.logDebug(F("Added new command implementation"));
	} else {
		flowControl.handleError(F("Limit of command handler implementations exceeded"));
	}
}

bool CommandHandler::validateCommandId(String& input) {
	if (isEmpty(input)) {
		flowControl.handleError(F("Empty command"));
		return false;
	}

	// Checking for the lenght of the input: it must be at least 5 (COMMAND_ID_LENGTH + 2) character
	// 3 (COMMAND_ID_LENGTH) characters for command ID, a space and at least one char for the rest
	if (input.length() < COMMAND_ID_LENGTH + 2) {
		flowControl.handleError(F("Command shorter then 5 character"), input);
		return false;
	}

	// Checking for invalid characters in the command ID
	// Every character must be an upper case letter
	char toCheck;
	for(byte i = 0; i < COMMAND_ID_LENGTH; i++) {
		toCheck = input.charAt(i);
		if (!isUpperCase(toCheck)) {
			flowControl.handleError(F("Invalid character in command ID"), String(toCheck));
			return false;
		}
	}

	// Checking for separator space character after command ID
	toCheck = input.charAt(COMMAND_ID_LENGTH);
	if (!isSpace(toCheck)) {
		flowControl.handleError(F("No space after the command ID"), input);
		return false;
	}

	logger.logDebug(F("Command ID validated"));
	return true;
}

String CommandHandler::getCommandId(String& input) {
	// Returning empty string in case of invalid command ID
	if (!validateCommandId(input)) {
		return "";
	}

	String commandId = input.substring(0, COMMAND_ID_LENGTH);
	return commandId;
}

void CommandHandler::handleCommand(String& input) {
	String commandId = getCommandId(input);
	if (isEmpty(commandId)) {
		// Simply returning since the error was alerady handled by the validation
		return;
	}

	String commandParameters = input.substring(COMMAND_ID_LENGTH + 1);

	// Checking if there is an implementation for the command ID or not
	AbstractCommand* commandImplementation;
	bool implementationFounded = false;
	for (byte i = 0; i < maxCommandImpl && !implementationFounded; i++) {
		commandImplementation = commandImplList[i];
		if (commandImplementation != NULL) {
			implementationFounded |= commandImplementation->supportsCommand(commandId);
		}
		else {
			logger.logError("NULL command implementation founded", String(i));
		}
	}

	if (!implementationFounded) {
		flowControl.handleError(F("Invalid command ID (no implementation founded)"), commandId);
		return;
	}

	logger.logDebug(F("Starting command processing"), input);

	commandImplementation->processCommand(commandId, commandParameters);
}
