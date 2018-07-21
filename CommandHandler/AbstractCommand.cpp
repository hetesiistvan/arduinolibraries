#include <AbstractCommand.h>

AbstractCommand::AbstractCommand(Logger& logger, FlowControl& flowControl)
	: logger(logger), flowControl(flowControl) {
}
