#ifndef CommandHandler_h
#define CommandHandler_h

#define SWITCH_PIN 4
#define MAX_IMPLEMENTATIONS 2

#include <Logger.h>
#include <FlowUtils.h>
#include <AbstractCommand.h>
#include <Arduino.h>

class CommandHandler: public FlowUtils {
	public:
		CommandHandler(Logger& logger, byte maxImplementations = MAX_IMPLEMENTATIONS);

		void addCommandImplementation(AbstractCommand& commandImpl);

		void handleCommand(String& input);

	private:
		Logger& logger;

		// Implementation of the commands
		// AbstractCommand (&commandImplList)[];
		AbstractCommand** commandImplList;
		byte commandImplCounter = 0;
		byte maxCommandImpl;

		void handleSuccess(String message);

		// Testing code
		const String COMMAND_ON = "ON";
		const String COMMAND_OFF = "OFF";
		boolean ledState = false;
};

#endif
