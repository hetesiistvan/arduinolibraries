#ifndef SerialFlowControl_H
#define SerialFlowControl_H

#include <FlowControl.h>
#include <StringUtils.h>
#include <Arduino.h>

class SerialFlowControl: public FlowControl
{
public:
	// Prints an error to the serial line
	void virtual handleError(String errorMessage);
	// Prints an error and a parameter to the serial line
	void virtual handleError(String errorMessage, String param);
	// Prints success message to the serial line
	void virtual handleSuccess(String message);

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
