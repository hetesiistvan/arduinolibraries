#ifndef BasicValidation_H
#define BasicValidation_H

#include <Arduino.h>

class BasicValidation {
	protected:
		// Returns true if the input is NULL or empty String
		bool isEmpty(String input);
};

#endif
