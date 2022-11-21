#ifndef LOGDATA_H
#define LOGDATA_H

#include "defs.h"
#include <HardwareSerial.h>

void initSDCard();

char *printSDMessage(Data ld);

void appendToFile(Data ld[5]);

HardwareSerial FC(2);

#define FC_TX 25
#define FC_RX 33
#define FC_STATE 32

void GetAndAppendFlightControlData(void);


#endif