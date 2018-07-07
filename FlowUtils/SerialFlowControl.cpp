#include <SerialFlowControl.h>

String SerialFlowControl::checkErrorMessageParameter(String param, String paramName) {
	if (!isEmpty(param)) {
		return param;
	}
	String checkedParamName = isEmpty(paramName) ? F("Param not specified") : paramName;
	String invalidInputMessage = F("Invalid input: ");
	return invalidInputMessage + checkedParamName;
}

void SerialFlowControl::handleError(String errorMessage, boolean closeLine) {
	if (! Serial ) {
		// Ignoring message if the serial line is not prepared
		return;
	}

	Serial.print(getErrPrefix());
	Serial.print(checkErrorMessageParameter(errorMessage, F("Error message")));
	if(closeLine) {
		Serial.println();
	}
}

void SerialFlowControl::handleError(String errorMessage) {
	if (! Serial ) {
		// Ignoring message if the serial line is not prepared
		return;
	}

	handleError(errorMessage, true);
}

void SerialFlowControl::handleError(String errorMessage, String param) {
	if (! Serial ) {
		// Ignoring message if the serial line is not prepared
		return;
	}

	handleError(errorMessage, false);
	Serial.println(checkErrorMessageParameter(param, F("Param")));
}

void SerialFlowControl::handleSuccess(String message) {
	if (! Serial ) {
		// Ignoring message if the serial line is not prepared
		return;
	}

	Serial.print(getSucPrefix());
	Serial.println(message);
}
