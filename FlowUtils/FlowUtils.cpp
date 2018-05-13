#include <FlowUtils.h>
#include <Arduino.h>

void FlowUtils::handleError(String errorMessage, boolean closeLine){
	Serial.print(F("ERR "));
	Serial.print(checkedParamValue(errorMessage, F("Error message")));
	if(closeLine) {
		Serial.println();
	}
}

void FlowUtils::handleError(String errorMessage, String param){
	handleError(errorMessage, false);
	Serial.println(checkedParamValue(param, F("Param")));
}

String FlowUtils::getCommandId(String& command) {
	return "";
}

bool FlowUtils::isEmpty(String input) {
	return input == NULL || input.length() == 0;
}

String FlowUtils::checkedParamValue(String param, String paramName) {
	if (!isEmpty(param)) {
		return param;
	}
	String checkedName = isEmpty(paramName) ? F("Param not specified") : paramName;
	String invalidInputMessage = F("Invalid input: ");
	return invalidInputMessage + checkedName;
}
