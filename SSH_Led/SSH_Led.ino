#include <Console.h>
 
const int ledPin = 13; // se declara el pin donde se conectará el LED
int incomingByte;      // la variable que contendrá la información de entrada
 
void setup() {
  // Se inicia la comunicación 
  Bridge.begin();
  Console.begin(); 
 
  while (!Console){
    ; // Se espera hasta que se conecte la consola
  }
  Console.println("Se ha conectado a la consola!!!!");
  // Se establece el pin donde se conecta el LED como salida
  pinMode(ledPin, OUTPUT);
}
 
void loop() {
  // Se verifica si hay información entrante
  if (Console.available() > 0) {
    // Se lee la información entrante
    incomingByte = Console.read();
    // Se hace la comparación. Si la entrada es una H (mayúscula) se enciende el LED
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
    } 
    // Si la entrada es una L (mayúscula), se apaga el LED
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
    }
  }
  delay(100);
}
