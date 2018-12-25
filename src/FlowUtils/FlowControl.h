#ifndef FlowControl_H
#define FlowControl_H

#include <StringUtils.h>
#include <Logger.h>
#include <Arduino.h>

class FlowControl
{
public:
	FlowControl(Logger& logger);

	// Empty handler for an error message (simply logs the message)
	void virtual handleError(String errorMessage);
	// Empty handler for an error message and a parameter (simply logs the message and the parameter)
	void virtual handleError(String errorMessage, String param);
	// Empty handler for a success message (simply logs the message)
	void virtual handleSuccess(String message);
protected:
	Logger& logger;

	// Check an input parameter for an error message and reports it's absence
	// Parameters:
	// param: The parameter to be verified
	// paramName: Parameter name to be used to report the absence of the parameter
	// Return: the param value if it's not empty else the paramName or
	// that is not defined either then a generic error message
	String checkErrorMessageParameter(String param, String paramName);

	// Checks the error message and applies a default one in case of absence
	String prepareErrorMessage(String message);
	// Checks the error message parameter and applies a default message in case of absence
	String prepareErrorParameter(String param);
	// Checks the success message and applies a default one in case of absence
	String prepareSuccessMessage(String message);

	// Returns the prefix used by displaying error
	String getErrPrefix();
	// Return the prefix used by displaying success message
	String getSucPrefix();
};

#endif
