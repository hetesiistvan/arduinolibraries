#include <FlowControl.h>
#include <Arduino.h>

#define COMMAND_ID_LENGTH 3

void FlowControl::handleError(String errorMessage, boolean closeLine){
	Serial.print(F("ERR "));
	Serial.print(checkedParamValue(errorMessage, F("Error message")));
	if(closeLine) {
		Serial.println();
	}
}

void FlowControl::handleError(String errorMessage, String param){
	handleError(errorMessage, false);
	Serial.println(checkedParamValue(param, F("Param")));
}

void FlowControl::handleSuccess(String message) {
	Serial.print(F("SUC "));
	Serial.println(message);
}
