#ifndef BasicValidation_H
#define BasicValidation_H

#include <Arduino.h>

class BasicValidation {
	protected:
		// Returns true if the input is NULL or empty String
		bool isEmpty(String input);
		// Check an input parameter and reports it's absence
		// Parameters:
		// param: The parameter to be verified
		// paramName: Parameter name to be used to report the absence of the parameter
		String checkedParamValue(String param, String paramName);
};

#endif
