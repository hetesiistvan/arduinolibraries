#include <AbstractDriver.h>

AbstractDriver::AbstractDriver(Logger& logger, FlowControl& flowControl)
	: logger(logger), flowControl(flowControl) {
}