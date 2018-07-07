#ifndef FlowControl_H
#define FlowControl_H

#include <StringUtils.h>
#include <Arduino.h>

class FlowControl {
	protected:
		// Prints an error to the serial line
		void handleError(String errorMessage);
		// Prints an error and a parameter to the serial line
		void handleError(String errorMessage, String param);
		// Prints success message to the serial line
		void handleSuccess(String message);

	private:
		// Check an input parameter for an error message and reports it's absence
		// Parameters:
		// param: The parameter to be verified
		// paramName: Parameter name to be used to report the absence of the parameter
		// Return: the param value if it's not empty else the paramName or
		// that is not defined either then a generic error message
		String checkErrorMessageParameter(String param, String paramName);

		// Prints an error to the serial line
		void handleError(String errorMessage, bool closeLine);
};

#endif
