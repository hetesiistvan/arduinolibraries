#include <FlowControl.h>

FlowControl::FlowControl(Logger& logger): logger(logger) {
}

String FlowControl::checkErrorMessageParameter(String param, String paramName) {
	if (!isEmpty(param)) {
		return param;
	}
	String checkedParamName = isEmpty(paramName) ? F("Param not specified") : paramName;
	String invalidInputMessage = F("Invalid input: ");
	return invalidInputMessage + checkedParamName;
}

String FlowControl::prepareErrorMessage(String message) {
	return checkErrorMessageParameter(message, F("Error message"));
}

String FlowControl::prepareErrorParameter(String param) {
	return checkErrorMessageParameter(param, F("Param"));
}

String FlowControl::prepareSuccessMessage(String message) {
	if (!isEmpty(message)) {
		return message;
	}
	else {
		String defaultMessage = F("Operation successful");
		return defaultMessage;
	}
}

void FlowControl::handleError(String errorMessage) {
	logger.logError(errorMessage);
}

void FlowControl::handleError(String errorMessage, String param) {
	logger.logError(errorMessage, param);
}

void FlowControl::handleSuccess(String message) {
	logger.logInfo(message);
}

String FlowControl::getErrPrefix() {
	return F("ERR ");
}

String FlowControl::getSucPrefix() {
	return F("SUC ");
}
