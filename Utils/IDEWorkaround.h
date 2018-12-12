#ifndef IDE_WORKAROUND_H
#define IDE_WORKAROUND_H

#include <Arduino.h>

#ifndef HAVE_HWSERIAL0

// Workaround to define variables which are defined by Arduino IDE
// but not available in other IDEs
HardwareSerial Serial(0, 0, 0, 0, 0, 0);

#endif

#endif