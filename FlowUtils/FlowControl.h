#ifndef FlowControl_H
#define FlowControl_H

#include <BasicValidation.h>
#include <Arduino.h>

class FlowControl: public BasicValidation {
	protected:
		// Prints an error to the serial line
		void handleError(String errorMessage, bool closeLine = true);
		// Prints an error and a parameter to the serial line
		void handleError(String errorMessage, String param);
		// Prints success message to the serial line
		void handleSuccess(String message);
};

#endif
