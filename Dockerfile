FROM ubuntu:18.10

ENV ARDUINO_IDE_HOME=/opt/arduino-ide \
ARDUINO_LIBRARY_FOLDER=/opt/arduino-libraries \
ARDUINO_UTILS_FOLDER=/opt/arduino-utils \
ARDUINO_IDE_VERSION=1.8.8

RUN apt-get update && \
apt-get install -y build-essential gcc-avr xz-utils && \
apt-get clean && \
rm -rf /var/lib/apt/lists/*

RUN mkdir -p ${ARDUINO_LIBRARY_FOLDER} ${ARDUINO_UTILS_FOLDER}

ADD https://www.arduino.cc/download.php?f=/arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz /tmp/arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz
RUN cd /tmp && \
xz -dc arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz | \
tar xf - && \
mv /tmp/arduino-${ARDUINO_IDE_VERSION} ${ARDUINO_IDE_HOME} && \
rm -f /tmp/arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz

ADD buildsketch.sh ${ARDUINO_UTILS_FOLDER}/
