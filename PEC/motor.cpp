#include "motor.h"
#include "Arduino.h"

//constructor
motor::motor(int pin){
    motorPin = pin;
    pinMode(motorPin, OUTPUT);
}
int motor::setVelocidad(int v){
    if(v<= 0) return -1;
    else if(v <= 70) {
      analogWrite(motorPin, 0);
      velocidadActual = 0;
      return 0;
    }
    else if(v <= 255){
        analogWrite(motorPin, 255); //ARRANCAMOS AL MAXIMO
        delay(260);
        analogWrite(motorPin, v);
        velocidadActual = v;
        return 1;
    }
    else {
        analogWrite(motorPin, 255);
        velocidadActual = 255;  
        return 2;
    }
}
//v entre 0 i 100
void motor::setVelocidadTotal(int v){

  return 0;
}
//valor que se escribe por el pin realmente
int motor::getVelocidad(){
    return velocidadActual;
}
//valor mapeado desde 0 a 100
int motor::getVelocidadTotal(){
    return map(velocidadActual,70, 255,0, 100);
}
