/*
RobotPopPet


Proyecto del curso de Programación I del programa de Ingeniería Electrónica de la Universidad del Quindío

El diseño de la estructura fue tomado de Thingverse, está disponible en el siguiente link:
https://www.thingiverse.com/thing:1634750

Para el manejo del robot se utilizó un Arduino Nano

El mapa de pines es:

11--> Servomotor izquierdo
12--> Servomotor derecho


Test de avance para robot PotPet Arduino

Desarrollado por César Augusto Álvarez Gaspar
Creado: 19/09/2018 

*/
//Demostración simple de variación de velocidad de servomotor
#include <Servo.h> 


//Declaración pines y sentidos
#define PINSERVODERECHO 12
#define PINSERVOIZQUIERDO 11
#define HORARIO 0
#define ANTIHORARIO 180
#define DETENIDO 90

//Enumeración para la codificación de la dirección
enum Edireccion {EAdelante,EAtraz,EDerecha,EIzquierda,EDetenido};

//Función para determinar la dirección del robot
void direccion(int opcion);


//Servo Motores de rotación continua
Servo ServoDerecho;
Servo ServoIzquierdo;

//Fija velocidad del servo:
  //0 , máxima velocidad en un sentido
  //90, punto muerto, servo está detenido
  //180, máxima velocidad en el otro sentido 
  

//Código de inicialización
void setup() 
{ 
  //Pin al que se encuentra conectado el servo
  ServoDerecho.attach(PINSERVODERECHO);
  ServoIzquierdo.attach(PINSERVOIZQUIERDO);
  direccion(EDetenido);  
} 

void loop() {
  //Rutina de prueba, se mueve en la direcciones de adelante, atraz, derecha y izquierda
  //Se detiene por 2 segundos entre cada cambio
  direccion(EAdelante);
  delay(2000);
  direccion(EDetenido);
  delay(2000);
  direccion(EAtraz);
  delay(2000);
  direccion(EDetenido);
  delay(2000);
  direccion(EDerecha);
  delay(2000);
  direccion(EDetenido);
  delay(2000);
  direccion(EIzquierda);
  delay(2000);
  direccion(EDetenido);
  delay(2000);
  }



void direccion(int opcion)
{
   //Seleción de la dirección a tomar, según la opción ingresada
   switch(opcion)
   {
    case EAdelante:
         ServoDerecho.write(HORARIO);
         ServoIzquierdo.write(ANTIHORARIO);
         break;
    case EAtraz:
         ServoDerecho.write(ANTIHORARIO);
         ServoIzquierdo.write(HORARIO);
         break;
    case EDerecha:
         ServoDerecho.write(ANTIHORARIO);
         ServoIzquierdo.write(ANTIHORARIO);
         break;
    case EIzquierda:
         ServoDerecho.write(HORARIO);
         ServoIzquierdo.write(HORARIO);
         break;
    case EDetenido:
         ServoDerecho.write(DETENIDO);
         ServoIzquierdo.write(DETENIDO);
         break;               
   }
   return;  
}
