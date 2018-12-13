#include <GetSetCommandImpl.h>

#define DRIVER_ID_LENGTH 3
#define DEVICE_ID_LENGTH 2
#define ON_LENGTH 2
#define OFF_LENGTH 3

GetSetCommandImpl::GetSetCommandImpl(Logger& logger, FlowControl& flowControl)
	: AbstractCommand(logger, flowControl) {
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

bool GetSetCommandImpl::validateGetParameters(String& getSetParameters) {
	if (getSetParameters.length() == DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH) {
		return validateParametersBase(getSetParameters);
	}
	else {
		// Invalid command parameter length
		flowControl.handleError(F("Invalid get parameter length (must be 6)"), getSetParameters);
		return false;
	}
}

bool GetSetCommandImpl::validateSetParameters(String& getSetParameters) {
	int paramLength = getSetParameters.length();
	if (paramLength == DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH + 1 + ON_LENGTH
		|| paramLength == DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH + 1 + OFF_LENGTH) {

		if (!validateParametersBase(getSetParameters)) {
			// Invalid base format
			return false;
		}

		// Base parameters needs to be followed by a space character
		char toCheck = getSetParameters.charAt(DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH);
		if (!isSpace(toCheck)) {
			flowControl.handleError(F("No space after the base parameters"), getSetParameters);
			return false;
		}

		// Checking last segment of the command
		String onOff = getSetParameters.substring(DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH + 1);
		if (!onOff.equals(getOnState()) && !onOff.equals(getOffState())) {
			flowControl.handleError(F("Invalid desired state"), getSetParameters);
			return false;
		}
	}
	else {
		// Invalid command parameter length
		flowControl.handleError(F("Invalid get parameter length (must be 9 / 10)"), getSetParameters);
		return false;
	}
	return true;
}

bool GetSetCommandImpl::validateParametersBase(String& getSetParameters) {
	// Validating driver ID
	char toCheck;
	for(byte i = 0; i < DRIVER_ID_LENGTH; i++) {
		toCheck = getSetParameters.charAt(i);
		if (!isUpperCase(toCheck)) {
			flowControl.handleError(F("Invalid character in driver ID"), String(toCheck));
			return false;
		}
	}

	// Checking space character after that
	toCheck = getSetParameters.charAt(DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH);
	if (!isSpace(toCheck)) {
		flowControl.handleError(F("No space after driver ID"), getSetParameters);
		return false;
	}

	// Checking device ID
	for(byte i = DRIVER_ID_LENGTH + 1; i < DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH; i++) {
		toCheck = getSetParameters.charAt(i);
		if (!isUpperCase(toCheck)) {
			flowControl.handleError(F("Invalid character in device ID"), String(toCheck));
			return false;
		}
	}

	return true;
}

String GetSetCommandImpl::getDriverId(String& getSetParameters) {
	String driverId = getSetParameters.substring(0, DRIVER_ID_LENGTH - 1);
	logger.logDebug(F("Selected driver ID"), driverId);
	return driverId;
}

byte GetSetCommandImpl::getDeviceId(String& getSetParameters) {
	String deviceId = getSetParameters.substring(DRIVER_ID_LENGTH + 1, DRIVER_ID_LENGTH + DEVICE_ID_LENGTH);
	logger.logDebug(F("Selected device ID"), deviceId);
	return deviceId.toInt();
}

bool GetSetCommandImpl::getDeviceState(String& getSetParameters) {
	String onOff = getSetParameters.substring(DRIVER_ID_LENGTH + 1 + DEVICE_ID_LENGTH + 1);
	logger.logDebug(F("Selected device state"), onOff);
	return onOff.equals(getOnState());
}

void GetSetCommandImpl::processGet(String& getSetParameters) {
	if (!validateGetParameters(getSetParameters)) {
		// Abort in case of invalid parameters
		// Error handling already happened before
		return;
	}

	String driverId = getDriverId(getSetParameters);
	int deviceID = getDeviceId(getSetParameters);

	if (deviceID != 0) {
		flowControl.handleError(F("Invalid device ID specified"), String(deviceID));
		return;
	}

	bool ledState = digitalRead(LED_BUILTIN) == HIGH;
	
	if (ledState) {
		flowControl.handleSuccess(F("Switch is ON"));
	}
	else {
		flowControl.handleSuccess(F("Switch is OFF"));
	}
}

void GetSetCommandImpl::processSet(String& getSetParameters) {
	if (!validateSetParameters(getSetParameters)) {
		// Abort in case of invalid parameters
		// Error handling already happened before
		return;
	}

	String driverId = getDriverId(getSetParameters);
	int deviceID = getDeviceId(getSetParameters);
	bool onOff = getDeviceState(getSetParameters);

	if (deviceID != 0) {
		flowControl.handleError(F("Invalid device ID specified"), String(deviceID));
		return;
	}

	bool ledState = digitalRead(LED_BUILTIN) == HIGH;

	// Note that code is here for test purposes
	if (onOff) {
		if (!ledState) {
			logger.logDebug(F("Turning on switch"));
			digitalWrite(LED_BUILTIN, HIGH);
			digitalWrite(SWITCH_PIN, HIGH);
			ledState = true;
			flowControl.handleSuccess(F("Switch turned on"));
		} else {
			logger.logDebug(F("LED already turned on"));
		}
	} else {
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

String GetSetCommandImpl::getOnState() {
	String onState = F("ON");
	return onState;
}

String GetSetCommandImpl::getOffState() {
	String offState = F("OFF");
	return offState;
}
