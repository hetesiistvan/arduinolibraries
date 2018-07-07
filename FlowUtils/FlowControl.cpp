#include <FlowControl.h>

void FlowControl::handleError(String errorMessage) {
}

void FlowControl::handleError(String errorMessage, String param) {
}

void FlowControl::handleSuccess(String message) {
}

String FlowControl::getErrPrefix() {
	return F("ERR ");
}

String FlowControl::getSucPrefix() {
	return F("SUC ");
}
