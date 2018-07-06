#ifndef BasicValidation_H
#define BasicValidation_H

#include <Arduino.h>

class BasicValidation {
	protected:
		// Returns true if the input is NULL or empty String
		bool isEmpty(String input);

		// Check an input parameter for an error message and reports it's absence
		// Parameters:
		// param: The parameter to be verified
		// paramName: Parameter name to be used to report the absence of the parameter
		// Return: the param value if it's not empty else the paramName or
		// that is not defined either then a generic error message
		String checkErrorMessageParameter(String param, String paramName);
};

#endif
