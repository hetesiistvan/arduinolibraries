#include <GetSetCommandImpl.h>

GetSetCommandImpl::GetSetCommandImpl(FlowControl& flowControl, Logger& logger)
	: AbstractCommand(flowControl, logger) {
}

bool GetSetCommandImpl::supportsCommand(String& command) {
	bool supports = false;
	supports |= command.equals(getGetName());
	supports |= command.equals(getSetName());
	return supports;
}

void GetSetCommandImpl::processCommand(String& commandId, String& commandParameters) {
	// Double checking if the command is supported or not
	if (!supportsCommand(commandId)) {
		flowControl.handleError(F("Command ID not supported"), commandId);
	}

	if (commandId.equals(getGetName())) {
		processGet(commandParameters);
	}
	else {
		processSet(commandParameters);
	}
}

void GetSetCommandImpl::processGet(String& commandParameters) {
	String line = "0";
	if (!commandParameters.equals(line)) {
		flowControl.handleError("Invalid line specified");
		return;
	}
	
	if (ledState) {
		flowControl.handleSuccess(F("Switch is ON"));
	}
	else {
		flowControl.handleSuccess(F("Switch is OFF"));
	}
}

void GetSetCommandImpl::processSet(String& commandParameters) {
	// Note that code is here for test purposes
	if (commandParameters.equals(COMMAND_ON)) {
		if (!ledState) {
			logger.logDebug(F("Turning on switch"));
			digitalWrite(LED_BUILTIN, HIGH);
			digitalWrite(SWITCH_PIN, HIGH);
			ledState = true;
			flowControl.handleSuccess(F("Switch turned on"));
		} else {
			logger.logDebug(F("LED already turned on"));
		}
	} else if (commandParameters.equals(COMMAND_OFF)) {
		if (ledState) {
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
		flowControl.handleError(F("Invalid request specified: "), commandParameters);
	}

}

String GetSetCommandImpl::getGetName() {
	String getName = F("GET");
	return getName;
}

String GetSetCommandImpl::getSetName() {
	String setName = F("SET");
	return setName;
}
