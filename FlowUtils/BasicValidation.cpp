#include <BasicValidation.h>
#include <Arduino.h>

bool BasicValidation::isEmpty(String input) {
	return input == NULL || input.length() == 0;
}

String BasicValidation::checkedParamValue(String param, String paramName) {
	if (!isEmpty(param)) {
		return param;
	}
	String checkedName = isEmpty(paramName) ? F("Param not specified") : paramName;
	String invalidInputMessage = F("Invalid input: ");
	return invalidInputMessage + checkedName;
}
