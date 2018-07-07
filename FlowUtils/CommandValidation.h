#ifndef CommandValidation_H
#define CommandValidation_H

#include <StringUtils.h>
#include <Arduino.h>

#define COMMAND_ID_LENGTH 3

class CommandValidation {
	protected:
		// Returns the command ID from a full command input from user
		String getCommandId(String& command);
};

#endif
