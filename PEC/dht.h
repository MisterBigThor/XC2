#ifndef dht_h
#define dht_h
#include "Arduino.h"

class dht{
  public:
      dht(int pin);
      float getTemperatura();
      float getHumedad();
  private:
      int sensorPin;
};

#endif



