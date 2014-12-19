#include <Process.h>

const int buttonPin = 2;
const int ledPin =  13;

int buttonState = 0;
Process p;

void setup() {
  Bridge.begin();
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT);     
  Serial.begin(57600);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {     
    digitalWrite(ledPin, HIGH);  
    p.runShellCommand("madplay /mnt/sd/THX.mp3");
    while(p.running());  
    Serial.println("it works!");
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }
}
