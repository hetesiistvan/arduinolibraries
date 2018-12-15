#!/bin/sh

if [ -z $1 ]; then
	echo "No sketch was specified. Aborting!"
	exit 1
fi

if [ -z $ARDUINO_IDE_HOME ]; then
	echo "ARDUINO_IDE_HOME not defined using default value: /opt/arduino-ide/current"
	ARDUINO_IDE_HOME=/opt/arduino-ide/current
fi

case "$ARDUINO_TARGET_BOARD" in
	uno)
		FQBN=arduino:avr:uno
		;;
	nano)
		FQBN=arduino:avr:nano
		;;
	*)
		echo "ARDUINO_TARGET_BOARD not defined, using default one: arduino:avr:uno"
		FQBN=arduino:avr:uno
esac

if [ -z $ARDUINO_LIBRARY_FOLDER ]; then
	ARDUINO_LIBRARY_FOLDER=$ARDUINO_IDE_HOME/libraries
fi

echo "Starting build using settings:"
echo "  ARDUINO_IDE_HOME = $ARDUINO_IDE_HOME"
echo "  FQBN = $FQBN"
echo "  ARDUINO_LIBRARY_FOLDER = $ARDUINO_LIBRARY_FOLDER"
echo "  JAVA_HOME = $JAVA_HOME"

cd $ARDUINO_IDE_HOME
${ARDUINO_IDE_HOME}/arduino-builder -hardware ${ARDUINO_IDE_HOME}/hardware -tools ${ARDUINO_IDE_HOME}/hardware/tools/avr -tools ${ARDUINO_IDE_HOME}/tools-builder -libraries $ARDUINO_LIBRARY_FOLDER -fqbn "$FQBN" $1
