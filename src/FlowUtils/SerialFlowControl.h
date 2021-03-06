#ifndef SerialFlowControl_H
#define SerialFlowControl_H

#include <FlowControl.h>
#include <StringUtils.h>
#include <Arduino.h>

class SerialFlowControl: public FlowControl
{
public:
	SerialFlowControl(Logger& logger);

	// Prints an error to the serial line
	void virtual handleError(String errorMessage) override;
	// Prints an error and a parameter to the serial line
	void virtual handleError(String errorMessage, String param) override;
	// Prints success message to the serial line
	void virtual handleSuccess(String message) override;

private:
	// Prints an error to the serial line
	void handleError(String errorMessage, bool closeLine);
};

#endif
