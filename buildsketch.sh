#!/bin/sh

if [ -z $ARDUINO_IDE_HOME ]; then
	echo "ARDUINO_IDE_HOME not defined using default value: /opt/arduino-ide/current"
	ARDUINO_IDE_HOME=/opt/arduino-ide/current
fi

${ARDUINO_IDE_HOME}/arduino-builder -hardware ${ARDUINO_IDE_HOME}/hardware -tools ${ARDUINO_IDE_HOME}/hardware/tools/avr -tools ${ARDUINO_IDE_HOME}/tools-builder -libraries /home/kishete/Arduino/libraries -fqbn "arduino:avr:uno" $1
