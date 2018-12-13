#include <SimpleList.h>

template<class T>
SimpleList<T>::SimpleList(Logger& logger, FlowControl& flowControl, byte maxListItems)
	: logger(logger), flowControl(flowControl), maxListItems(maxListItems) {
	listItems = new T*[maxListItems];
}

template<class T>
bool SimpleList<T>::addItem(T& item) {
	if (listItemCounter +1 <= maxListItems) {
		if (!item) {
			flowControl.handleError(F("Null value can not be added"));
			return false;
		}
		listItems[listItemCounter] = &item;
		listItemCounter++;
		logger.logDebug(F("Added new list item"));
	} else {
		flowControl.handleError(F("Limit of list items exceeded"));
		return false;
	}
	return true;
}

template<class T>
T* SimpleList<T>::getItem(byte index) {
	if (index < maxListItems) {
		return listItems[index];
	}
	else {
		flowControl.handleError(F("Index out of range"), String(index));
		return NULL;
	}
}

template<class T>
byte SimpleList<T>::getSize() {
	return listItemCounter;
}
