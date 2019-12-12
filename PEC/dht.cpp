#include "dht.h"
#include "Arduino.h"

dht::dht(int pin){
  sensorPin=pin;
}
float dht::getHumedad(){
  return 0;  
}
float dht::getTemperatura(){
  return 0;
}

