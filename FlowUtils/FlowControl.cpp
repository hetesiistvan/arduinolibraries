#include <FlowControl.h>
#include <Arduino.h>

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
