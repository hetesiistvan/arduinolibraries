#ifndef CommandHandler_h
#define CommandHandler_h

#ifndef SWITCH_PIN
#define SWITCH_PIN 4
#endif

#include <Logger.h>
#include <Arduino.h>

class CommandHandler
{
  public:
    CommandHandler(Logger& logger);

    void addCommandHandler();
    void addConfigHandler();
    void addGetHandler();
    void addSetHandler();
    void addDiagHandler();

	void handleCommand(String& input);

    void handleError(String errorMessage);
    void handleError(String errorMessage, String param);

  private:
    // TODO kishete 2017.12.28: add a getter - setter pair for that
    Logger& logger;

    const String ERROR_PREFIX = "ERR ";
    const String SUCCESS_PREFIX = "SUC ";

    void handleSuccess(String message);

	// Testing code
	const String COMMAND_ON = "ON";
	const String COMMAND_OFF = "OFF";
	boolean ledState = false;
};

#endif
