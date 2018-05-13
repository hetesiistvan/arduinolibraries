#ifndef FlowUtils_H
#define FlowUtils_H

#include <Arduino.h>

class FlowUtils {
	protected:
		// Prints an error to the serial line
		void handleError(String errorMessage, bool closeLine = true);
		// Prints an error and a parameter to the serial line
		void handleError(String errorMessage, String param);
		// Returns the command ID from a full command input from user
		String getCommandId(String& command);
		// Returns true if the input is NULL or empty String
		bool isEmpty(String input);
		// Check an input parameter and reports it's absence
		// Parameters:
		// param: The parameter to be verified
		// paramName: Parameter name to be used to report the absence of the parameter
		String checkedParamValue(String param, String paramName);
};

#endif
