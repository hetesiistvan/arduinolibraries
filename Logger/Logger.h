#ifndef Logger_h
#define Logger_h

#include <Arduino.h>

#define LOG_LEVEL_FATAL 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_INFO 3
#define LOG_LEVEL_DEBUG 4

class Logger
{
public:
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

	String getLogPrefix(int level);

	void logMessage(int level, String message);
	void logMessage(int level, String message, int value);
	void logMessage(int level, String message, String arg);
};

#endif
