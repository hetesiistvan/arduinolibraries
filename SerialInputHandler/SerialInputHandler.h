#ifndef SerialInputHandler_h
#define SerialInputHandler_h

#include <Logger.h>
#include <CommandHandler.h>
#include <Arduino.h>

#define INPUT_BUFFER_MAX_LEN 30

class SerialInputHandler
{
  public:
    SerialInputHandler(Logger &logger, CommandHandler &commandHandler, int inputBufferLength = INPUT_BUFFER_MAX_LEN);

	void initSerialInputHandler();
    void handleSerialInput();
    void checkSerialTimeout();

  private:
    // TODO kishete 2017.12.28: add a getter - setter pair for those members
    Logger& logger;
    CommandHandler& commandHandler;

    String inputBuffer;
    byte inputBufferLength;
    unsigned int timeout = 0; // Timeout value in milisecond
    unsigned long timerStartValue = 0; // Current start time in miliseconds

    void processSerialInputByte(char input);
    void handleCommandReceived();
    void checkBufferLimit();
    void rejectInput(String errorMsg);
    void resetInputBuffer();
    void setupSerialTimeout();
};

#endif
