/*
 * MAIN PEC
 * 
 */
#include "motor.h"
#include "ledAlive.h"

motor m(3);
ledAlive l(10);

//LDR
// valores cercanos a 0 LUZ
// valores cercanos a 5 oscuridad
const float Vin_LDR = 5.0; //Si se alimenta con 5V, tambien puede ser 3V
const String LdrTAG = "LDR: ";
const int puerto_lectura_LDR = A5;
const String opciones="1. reiniciar Arduino\n2.Dar Velocidad Motor\n3.ApagarMotor\n4.Leer Luz\n5.Ver temperatura\n6.Ver Humedad";

void setup() {
  Serial.begin(9600);
  pinMode(puerto_lectura_LDR,INPUT);
  Serial.println("ARDUINO SETUP COMPLET");
}

void loop() {
  /*
  Serial.println(opciones);
  Serial.println("introduzaca una opcion");
  if(Serial.available() > 0){
    String str = Serial.readStringUntil('\n');
    switch(str.toInt()){
        case 1:
          Serial.println("Reiniciando");
          break;
        case 2:
          Serial.println("Introduzca un valor para el motor 0-100");
          //m.set()
          break;
        case 3:
          break;
        case 4:
          break;
        default:
          Serial.println("no se ha reconocido el comando");
          break;
    }
  }
  */
  comprobarLDR();
  comprobarMotor();
  l.actLedAlive(0);
  delay(500);
}

int comprobarMotor(){
    if(Serial.available()){
      String str = Serial.readStringUntil('\n');
      m.setVelocidad(str.toInt());
    }
}
float comprobarLDR(){
  long lectura;
  float Voltaje_R2=0;
  // Leemos el valor en el pin puerto_lectura_LDR
  lectura=analogRead(puerto_lectura_LDR);
  // Calculamos el voltaje en la resistencia desconocida
  Voltaje_R2=(Vin_LDR/1023.0)*lectura;
  // Lo imprimimos en el Monitor Serie
  Serial.println(Voltaje_R2,2);
  return Voltaje_R2;
}
