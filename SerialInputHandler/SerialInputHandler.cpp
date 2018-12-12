#include <SerialInputHandler.h>
#include <IDEWorkaround.h>

SerialInputHandler::SerialInputHandler(Logger& logger, CommandHandler& commandHandler, FlowControl& flowControl, int inputBufferLength)
	: logger(logger), commandHandler(commandHandler), flowControl(flowControl), inputBufferLength(inputBufferLength) {
}

void SerialInputHandler::initSerialInputHandler() {
	inputBuffer.reserve(inputBufferLength);
	resetInputBuffer();
}

void SerialInputHandler::handleSerialInput() {
	while (Serial.available()) {
		char inputChar = (char) Serial.read();
		setupSerialTimeout();
		processSerialInputByte(inputChar);
	}
}

void SerialInputHandler::processSerialInputByte(char input) {
	if (input == '\n') {
		handleCommandReceived();
	} else {
		inputBuffer += input;
		checkBufferLimit();
	}
}

void SerialInputHandler::handleCommandReceived() {
	logger.logDebug(F("Command received: "), inputBuffer);
	commandHandler.handleCommand(inputBuffer);
	resetInputBuffer();
}

void SerialInputHandler::checkBufferLimit() {
	if ( inputBuffer.length() == inputBufferLength ) {
		// Input is too long, rejecting it
		rejectInput(F("Invalid command - too long: "));
	}
}

void SerialInputHandler::rejectInput(String errorMsg) {
	flowControl.handleError(errorMsg, inputBuffer);
	resetInputBuffer();
}

void SerialInputHandler::resetInputBuffer() {
	inputBuffer = "";
	if (timeout) {
		timerStartValue = 0;
	}
}

void SerialInputHandler::setupSerialTimeout() {
	if (timeout && inputBuffer.length() == 0) {
		// Starting timer
		timerStartValue = millis();
	}
}

void SerialInputHandler::checkSerialTimeout() {
	if (timeout) {
		unsigned long currentTime = millis();
		if (currentTime - timerStartValue > timeout) {
			// Timeout occurred
			rejectInput(F("Timeout occurred: "));
		}
	}
}
