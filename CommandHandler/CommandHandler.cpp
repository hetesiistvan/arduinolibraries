#include <CommandHandler.h>

CommandHandler::CommandHandler(Logger& logger, FlowControl& flowControl, byte maxImplementations)
	: logger(logger), flowControl(flowControl) {
	commandImplList = new AbstractCommand*[maxImplementations];
}

void CommandHandler::addCommandImplementation(AbstractCommand& commandImpl) {
	if (commandImplCounter +1 <= maxCommandImpl) {
		commandImplList[commandImplCounter] = &commandImpl;
		decorateCommandImplementation(commandImpl);
		commandImplCounter++;
		logger.logDebug(F("Added new command implementation"));
	} else {
		flowControl.handleError(F("Limit of command handler implementations exceeded"));
	}
}

void CommandHandler::decorateCommandImplementation(AbstractCommand& commandImpl) {
	commandImpl.setFlowControl(flowControl);
}

bool CommandHandler::validateCommandId(String& input) {
	if (isEmpty(input)) {
		flowControl.handleError(F("Empty command"));
		return false;
	}

	// Checking for the lenght of the input: it must be at least 5 (COMMAND_ID_LENGTH + 2) character
	// 3 (COMMAND_ID_LENGTH) characters for command ID, a space and at least one char for the rest
	if (input.length() < COMMAND_ID_LENGTH + 2) {
		flowControl.handleError(F("Command shorter then 5 character"));
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
		flowControl.handleError(F("No space after the command ID"));
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

	String commandId = input.substring(0, COMMAND_ID_LENGTH - 1);
	return commandId;
}

void CommandHandler::handleCommand(String& input) {
	// Note that code is here for test purposes
	if ( input.equals(COMMAND_ON) ) {
		if ( !ledState ) {
			logger.logDebug(F("Turning on switch"));
			digitalWrite(LED_BUILTIN, HIGH);
			digitalWrite(SWITCH_PIN, HIGH);
			ledState = true;
			flowControl.handleSuccess(F("Switch turned on"));
		} else {
			logger.logDebug(F("LED already turned on"));
		}
	} else if ( input.equals(COMMAND_OFF) ) {
		if ( ledState ) {
			logger.logDebug(F("Turning off switch"));
			digitalWrite(LED_BUILTIN, LOW);
			digitalWrite(SWITCH_PIN, LOW);
			ledState = false;
			flowControl.handleSuccess(F("Switch turned off"));
		}
		else {
			logger.logDebug(F("LED already turned off"));
		}
	} else {
		flowControl.handleError(F("Invalid command specified: "), input);
	}
}
