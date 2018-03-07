#ifndef CommandHandler_h
#define CommandHandler_h

#include <Logger.h>
#include <Arduino.h>

class CommandHandler
{
  public:
    CommandHandler(Logger &refLogger);

    void handleInput(String input);

    void addCommandHandler();
    void addConfigHandler();
    void addGetHandler();
    void addSetHandler();
    void addDiagHandler();

    void handleError(String errorMessage);
    void handleError(String errorMessage, String param);

  private:
    // TODO kishete 2017.12.28: add a getter - setter pair for that
    Logger &logger;

    const String ERROR_PREFIX = "ERR ";
    const String SUCCESS_PREFIX = "SUC ";

    void handleSuccess(String message);
};

#endif
