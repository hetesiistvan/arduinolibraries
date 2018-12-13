#ifndef SimpleList_H
#define SimpleList_H

#include <Logger.h>
#include <FlowControl.h>

#define MAX_LIST_SIZE 5

template<class T>
class SimpleList
{
public:
	SimpleList(Logger& logger, FlowControl& flowControl, byte maxListItems = MAX_LIST_SIZE);

	bool addItem(T& item);
	T* getItem(byte index);
	byte getSize();

private:
	Logger& logger;
	FlowControl& flowControl;

	// Shows how many items were already added to the list
	byte listItemCounter = 0;
	// Maximum number of the list items
	byte maxListItems = 0;

	// List items
	T** listItems;
};

#endif