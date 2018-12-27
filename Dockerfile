FROM ubuntu:18.10

ENV ARDUINO_IDE_HOME=/opt/arduino-ide \
ARDUINO_LIBRARY_FOLDER=/opt/arduino-libraries \
ARDUINO_UTILS_FOLDER=/opt/arduino-utils \
ARDUINO_IDE_VERSION=1.8.8

RUN apt-get -q update && \
apt-get install -q -y gcc-avr avr-libc gcc g++ libc6-dev && \
apt-get -q clean && \
rm -rf /var/lib/apt/lists/*

COPY build/image .
