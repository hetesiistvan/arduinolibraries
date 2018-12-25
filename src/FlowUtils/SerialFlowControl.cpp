#include <SerialFlowControl.h>
#include <IDEWorkaround.h>

SerialFlowControl::SerialFlowControl(Logger& logger): FlowControl(logger) {
}

void SerialFlowControl::handleError(String errorMessage, boolean closeLine) {
	Serial.print(getErrPrefix());
	Serial.print(errorMessage);
	if(closeLine) {
		Serial.println();
	}
	else {
		// Since we use this option when we pass a parameter to the message then we can use this
		// to write a separator
		Serial.print(" : ");
	}
}

void SerialFlowControl::handleError(String errorMessage) {
	String checkedMessage = prepareErrorMessage(errorMessage);
	FlowControl::handleError(checkedMessage);

	if (! Serial ) {
		// Ignoring message if the serial line is not prepared
		return;
	}

	handleError(checkedMessage, true);
}

void SerialFlowControl::handleError(String errorMessage, String param) {
	String checkedMessage = prepareErrorMessage(errorMessage);
	String checkedParam = prepareErrorParameter(param);
	FlowControl::handleError(checkedMessage, checkedParam);

	if (! Serial ) {
		// Ignoring message if the serial line is not prepared
		return;
	}

	handleError(checkedMessage, false);
	Serial.println(checkedParam);
}

void SerialFlowControl::handleSuccess(String message) {
	String checkedMessage = prepareSuccessMessage(message);
	FlowControl::handleSuccess(checkedMessage);

	if (! Serial ) {
		// Ignoring message if the serial line is not prepared
		return;
	}

	Serial.print(getSucPrefix());
	Serial.println(checkedMessage);
}
