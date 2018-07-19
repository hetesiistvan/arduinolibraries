#ifndef GetSetCommandImpl_H
#define GetSetCommandImpl_H

#include <AbstractCommand.h>

#define SWITCH_PIN 4

class GetSetCommandImpl: public AbstractCommand
{
public:
	virtual void processCommand(String& commandId, String& commandParameters);
	virtual bool supportsCommand(String& command);

private:
	// Name of GET command
	String getGetName();
	// Name of SET command
	String getSetName();

	void processGet(String& commandParameters);
	void processSet(String& commandParameters);

	// Testing code
	const String COMMAND_ON = "ON";
	const String COMMAND_OFF = "OFF";
	boolean ledState = false;
};

#endif
