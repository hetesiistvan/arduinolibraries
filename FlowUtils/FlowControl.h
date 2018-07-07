#ifndef FlowControl_H
#define FlowControl_H

#include <StringUtils.h>
#include <Arduino.h>

class FlowControl {
	protected:
		// Empty handler for an error message
		void virtual handleError(String errorMessage);
		// Empty handler for an error message and a parameter
		void virtual handleError(String errorMessage, String param);
		// Empty handler for a success message
		void virtual handleSuccess(String message);
};

#endif
