#ifndef motor_h
#define motor_h
#include "Arduino.h"

class motor{
    public:
      motor(int pin);
      int setVelocidad(int v); 
      void setVelocidadTotal(int v);
      int getVelocidad();
      int getVelocidadTotal();
    private:
      int motorPin;
      int velocidadActual;
      const String motorTag ="motorPwm: ";
};
#endif
