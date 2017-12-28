#include <Arduino.h>
#include <Logger.h>

Logger::Logger(int setLevel):
  LOG_MESSAGES {
    F("LOG FATAL: "),
    F("LOG ERROR: "),
    F("LOG WARN"),
    F("LOG INFO: "),
    F("LOG DEBUG: ")
  }
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

void Logger::logMessage(int level, String message) {
  if (level >= logLevel && Serial) {
    Serial.print(LOG_MESSAGES[level]);
    Serial.println(message);
  }
}

void Logger::logMessage(int level, String message, int value) {
  if (level >= logLevel && Serial) {
    Serial.print(LOG_MESSAGES[level]);
    Serial.print(message);
    Serial.println(value);
  }
}

void Logger::logFatal(String message) {
  logMessage(LOG_LEVEL_FATAL, message);
}


void Logger::logFatal(String message, int value) {
  logMessage(LOG_LEVEL_FATAL, message, value);
}

void Logger::logError(String message) {
  logMessage(LOG_LEVEL_ERROR, message);
}


void Logger::logError(String message, int value) {
  logMessage(LOG_LEVEL_ERROR, message, value);
}

void Logger::logWarn(String message) {
  logMessage(LOG_LEVEL_WARN, message);
}


void Logger::logWarn(String message, int value) {
  logMessage(LOG_LEVEL_WARN, message, value);
}

void Logger::logInfo(String message) {
  logMessage(LOG_LEVEL_INFO, message);
}

void Logger::logInfo(String message, int value) {
  logMessage(LOG_LEVEL_INFO, message, value);
}

void Logger::logDebug(String message) {
  logMessage(LOG_LEVEL_DEBUG, message);
}

void Logger::logDebug(String message, int value) {
  logMessage(LOG_LEVEL_DEBUG, message, value);
}
