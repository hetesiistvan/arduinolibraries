#ifndef Logger_h
#define Logger_h

#include <Arduino.h>

class Logger
{
  public:
    static const int LOG_LEVEL_FATAL = 0;
    static const int LOG_LEVEL_ERROR = 1;
    static const int LOG_LEVEL_WARN = 2;
    static const int LOG_LEVEL_INFO = 3;
    static const int LOG_LEVEL_DEBUG = 4;

    Logger(int setLevel);
    void setLogLevel(int setLevel);

    void logFatal(String message);
    void logFatal(String message, int value);
    void logFatal(String message, String arg);
    void logError(String message);
    void logError(String message, int value);
    void logError(String message, String arg);
    void logWarn(String message);
    void logWarn(String message, int value);
    void logWarn(String message, String arg);
    void logInfo(String message);
    void logInfo(String message, int value);
    void logInfo(String message, String arg);
    void logDebug(String message);
    void logDebug(String message, int value);
    void logDebug(String message, String arg);

  private:
    int logLevel;
    String LOG_MESSAGES[5];

    void logMessage(int level, String message);
    void logMessage(int level, String message, int value);
    void logMessage(int level, String message, String arg);
};

#endif
