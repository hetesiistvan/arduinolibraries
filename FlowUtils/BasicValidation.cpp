#include <BasicValidation.h>
#include <Arduino.h>

bool BasicValidation::isEmpty(String input) {
	return input == NULL || input.length() == 0;
}
