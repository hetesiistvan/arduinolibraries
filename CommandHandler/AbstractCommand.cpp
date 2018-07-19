#include <AbstractCommand.h>

AbstractCommand::AbstractCommand(FlowControl& flowControl, Logger& logger)
	: flowControl(flowControl), logger(logger) {
}
