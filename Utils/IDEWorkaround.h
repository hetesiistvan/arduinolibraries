#ifndef IDE_WORKAROUND_H
#define IDE_WORKAROUND_H

#ifndef ARDUINO_IDE

// Workaround to define variables which are defined by Arduino IDE
// but not available in other IDEs
#include <Arduino.h>
HardwareSerial Serial;

#endif

#endif