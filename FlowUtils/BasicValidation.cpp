#include <BasicValidation.h>
#include <Arduino.h>

bool BasicValidation::isEmpty(String input) {
	return input == NULL || input.length() == 0;
}

String BasicValidation::checkErrorMessageParameter(String param, String paramName) {
	if (!isEmpty(param)) {
		return param;
	}
	String checkedParamName = isEmpty(paramName) ? F("Param not specified") : paramName;
	String invalidInputMessage = F("Invalid input: ");
	return invalidInputMessage + checkedParamName;
}
