#include "ledAlive.h"
#include "Arduino.h"

ledAlive::ledAlive(int pin){
    pinLedAlive = pin;
    pinMode(pin,OUTPUT);
    ledAliveStatus = 0;
}

void ledAlive::actLedAlive(int forceStatus){
    digitalWrite(pinLedAlive, ledAliveStatus>2);
    
    ledAliveStatus++;
    if(ledAliveStatus >10) ledAliveStatus = 0;
    return;
}
