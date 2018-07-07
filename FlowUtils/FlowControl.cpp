#include <FlowControl.h>
#include <Arduino.h>

String FlowControl::checkErrorMessageParameter(String param, String paramName) {
	if (!isEmpty(param)) {
		return param;
	}
	String checkedParamName = isEmpty(paramName) ? F("Param not specified") : paramName;
	String invalidInputMessage = F("Invalid input: ");
	return invalidInputMessage + checkedParamName;
}

void FlowControl::handleError(String errorMessage, boolean closeLine){
	Serial.print(F("ERR "));
	Serial.print(checkErrorMessageParameter(errorMessage, F("Error message")));
	if(closeLine) {
		Serial.println();
	}
}

void FlowControl::handleError(String errorMessage, String param){
	handleError(errorMessage, false);
	Serial.println(checkErrorMessageParameter(param, F("Param")));
}

void FlowControl::handleSuccess(String message) {
	Serial.print(F("SUC "));
	Serial.println(message);
}
