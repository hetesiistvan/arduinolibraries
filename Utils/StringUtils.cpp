#include <StringUtils.h>
#include <Arduino.h>

bool isEmpty(String input) {
	return input == NULL || input.length() == 0;
}
