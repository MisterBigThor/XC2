#ifndef ledAlive_h
#define ledAlive_h
#include "Arduino.h"

class ledAlive{
    public:
        ledAlive(int pin);
         void actLedAlive(int forceStatus);
    private:
        int pinLedAlive;
        int ledAliveStatus;
       
};

#endif
