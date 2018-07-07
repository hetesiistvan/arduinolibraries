#include <CommandHandler.h>

CommandHandler::CommandHandler(Logger& logger, FlowControl& flowControl, byte maxImplementations)
	: logger(logger), flowControl(flowControl) {
	commandImplList = new AbstractCommand*[maxImplementations];
}

void CommandHandler::addCommandImplementation(AbstractCommand& commandImpl) {
	if (commandImplCounter +1 <= maxCommandImpl) {
		commandImplList[commandImplCounter] = &commandImpl;
		commandImplCounter++;
	} else {

	}
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
		logger.logError(F("Invalid command specified: "), input);
		flowControl.handleError(F("Invalid command specified: "), input);
	}
}
