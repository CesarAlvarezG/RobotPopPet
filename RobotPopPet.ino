/*
RobotPopPet


Proyecto del curso de Programación I del programa de Ingeniería Electrónica de la Universidad del Quindío

El diseño de la estructura fue tomado de Thingverse, está disponible en el siguiente link:
https://www.thingiverse.com/thing:1634750

Para el manejo del robot se utilizó un Arduino Nano

El mapa de pines es:

11--> Servomotor izquierdo
12--> Servomotor derecho

Mando por el puerto serial de robot PopPet
Test de avance para robot PotPet Arduino

Desarrollado por César Augusto Álvarez Gaspar
Creado: 5/02/2019 
Modificado: 27/02/2019


*/

#include <Servo.h> 
#include <SoftwareSerial.h>


//Declaración pines y sentidos
#define PINSERVODERECHO 12
#define PINSERVOIZQUIERDO 11
#define HORARIO 0
#define ANTIHORARIO 180
#define DETENIDO 90
#define PITO 4
#define TXBluetooth 3
#define RXBluetooth 2

//Enumeración para la codificación de la dirección
enum Edireccion {EAdelante,EAtraz,EDerecha,EIzquierda,EDetenido};

//Función para determinar la dirección del robot
void direccion(int opcion);

//Función para cumplir las ordenes indicadas por el puerto serial
void mandoSerial(char letra);

//Función para cumplir las ordenes indicadas por el puerto serial
void testMotores(void);

//Función para realizar una celebración
void celebrar(void);


//Servo Motores de rotación continua
Servo ServoDerecho;
Servo ServoIzquierdo;

//Declaración de la interfaz del modulo Bluetooth
SoftwareSerial BT(RXBluetooth,TXBluetooth);


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
  Serial.begin(9600);
  pinMode(PITO,OUTPUT);//Pin al que esta conectado el pito
  digitalWrite(PITO,LOW);
  BT.begin(9600);
} 

char orden;
int velocidad=10;//Variable con la velocidad del robot
//Rango de velocidad de 0 a 100

void loop()
{
  if(Serial.available() > 0)
    {
      orden=Serial.read();
      mandoSerial(orden);
      Serial.write(orden);
    }
  if(BT.available() > 0)
    {
      orden=BT.read();
      mandoSerial(orden);
      Serial.write(orden);
    }    
}


//Función para determinar la dirección teniendo en cuenta la velocidad
void direccion(int opcion)
{
   switch(opcion)
   {
    case EAdelante:
         ServoDerecho.write(0.9*HORARIO*velocidad+DETENIDO);
         ServoIzquierdo.write(0.9*ANTIHORARIO*velocidad+DETENIDO);
         break;
    case EAtraz:
         ServoDerecho.write(0.9*ANTIHORARIO*velocidad+DETENIDO);
         ServoIzquierdo.write(0.9*HORARIO*velocidad+DETENIDO);
         break;
    case EDerecha:
         ServoDerecho.write(0.9*ANTIHORARIO*velocidad+DETENIDO);
         ServoIzquierdo.write(0.9*ANTIHORARIO*velocidad+DETENIDO);
         break;
    case EIzquierda:
         ServoDerecho.write(0.9*HORARIO*velocidad+DETENIDO);
         ServoIzquierdo.write(0.9*HORARIO*velocidad+DETENIDO);
         break;
    case EDetenido:
         ServoDerecho.write(DETENIDO);
         ServoIzquierdo.write(DETENIDO);
         break;
    default:
         ServoDerecho.write(DETENIDO);
         ServoIzquierdo.write(DETENIDO);
         break;               
   }
   return;  
}

//Función para realizar pruebas por medio del monitor serie
//Se utilizó la configuración de mando de juegos en teclado
void mandoSerial(char letra)
{
  switch(letra)
   {
    case 'w':
             direccion(EAdelante);
             break;
    case 'x':
             direccion(EAtraz);
             break;         
    case 'a':
             direccion(EIzquierda);
             break;
    case 'd':
             direccion(EDerecha);
             break;
    case 's':
             direccion(EDetenido);
             break;
    case 't':
             testMotores();
             break;
    case '-':
             velocidad=50;
             break;
    case '+':
             velocidad=100;
             break;
    case 'p':
             digitalWrite(PITO,HIGH);
             break;
    case 'n':
             digitalWrite(PITO,LOW);
             break;
    case 'c':
             celebrar();
             break;
   }                            
}

//Función para realizar pruebas de los motores
void testMotores(void)
{
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

void celebrar(void)
{
  //Rutina de celebración
  //Se detiene por 1 segundo entre cada cambio
  for(int i=0;i<=4;i++)
  {
      direccion(EDerecha);
      digitalWrite(PITO,HIGH);
      delay(500);
      direccion(EIzquierda);
      digitalWrite(PITO,LOW);
      delay(500);    
  }
}
