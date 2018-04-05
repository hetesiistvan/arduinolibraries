#include <Arduino.h>
#include <Logger.h>

Logger::Logger(int setLevel)
{
  setLogLevel(setLevel);
}

void Logger::setLogLevel(int setLevel) {
  if ( setLevel >= LOG_LEVEL_FATAL && setLevel <= LOG_LEVEL_DEBUG ) {
    logLevel = setLevel;
  }
  else {
    logLevel = LOG_LEVEL_WARN;
    logWarn(F("Invalid log level specified, using WARN: "), setLevel);
  }
}

String Logger::getLogPrefix(int level) {
	// Log message prefixes are not defined in the order of their log level,
	// but in the probability of their usage. This was done to save execution time.
	switch (level) {
		case LOG_LEVEL_INFO : return F("LOG INFO: ");
		case LOG_LEVEL_ERROR : return F("LOG ERROR: ");
		case LOG_LEVEL_DEBUG : return F("LOG DEBUG: ");
		case LOG_LEVEL_WARN : return F("LOG WARN");
		case LOG_LEVEL_FATAL : return F("LOG FATAL: ");
		default: return F("UNKNOWN LOG LEVEL: ");
	}
}

void Logger::logMessage(int level, String message) {
  if (level <= logLevel && Serial) {
    Serial.print(getLogPrefix(level));
    Serial.println(message);
  }
}

void Logger::logMessage(int level, String message, int value) {
  if (level <= logLevel && Serial) {
    Serial.print(getLogPrefix(level));
    Serial.print(message);
    Serial.println(value);
  }
}

void Logger::logMessage(int level, String message, String arg) {
  if (level <= logLevel && Serial) {
    Serial.print(getLogPrefix(level));
    Serial.print(message);
    Serial.println(arg);
  }
}

void Logger::logFatal(String message) {
  logMessage(LOG_LEVEL_FATAL, message);
}


void Logger::logFatal(String message, int value) {
  logMessage(LOG_LEVEL_FATAL, message, value);
}

void Logger::logFatal(String message, String arg) {
  logMessage(LOG_LEVEL_FATAL, message, arg);
}

void Logger::logError(String message) {
  logMessage(LOG_LEVEL_ERROR, message);
}


void Logger::logError(String message, int value) {
  logMessage(LOG_LEVEL_ERROR, message, value);
}

void Logger::logError(String message, String arg) {
  logMessage(LOG_LEVEL_ERROR, message, arg);
}

void Logger::logWarn(String message) {
  logMessage(LOG_LEVEL_WARN, message);
}


void Logger::logWarn(String message, int value) {
  logMessage(LOG_LEVEL_WARN, message, value);
}

void Logger::logWarn(String message, String arg) {
  logMessage(LOG_LEVEL_WARN, message, arg);
}

void Logger::logInfo(String message) {
  logMessage(LOG_LEVEL_INFO, message);
}

void Logger::logInfo(String message, int value) {
  logMessage(LOG_LEVEL_INFO, message, value);
}

void Logger::logInfo(String message, String arg) {
  logMessage(LOG_LEVEL_INFO, message, arg);
}

void Logger::logDebug(String message) {
  logMessage(LOG_LEVEL_DEBUG, message);
}

void Logger::logDebug(String message, int value) {
  logMessage(LOG_LEVEL_DEBUG, message, value);
}

void Logger::logDebug(String message, String arg) {
  logMessage(LOG_LEVEL_DEBUG, message, arg);
}
