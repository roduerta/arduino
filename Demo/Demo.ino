// VUMETRO LED
// Un vumetro led consiste en iluminar gradualmente un grupo de leds, dependiendo de la intensidad del sonido recibido
// Al conectar el microfono a la salida A0 analogica, esta nos va a delvover valores de 0 a 1023, dependiendo del voltaje
// Con MINSONIDO y MAXSONIDO fijamos el rango de captura ignorando lecturas fuera de ese rango
// En cada ciclo se calcula un valor medio tomando como referencias las n NUMLECTURAS anteriores
// Por último el valor medio obtenido se transforma a un valor entre primerLED y ultimoLED. Dicho valor representa el numero de leds a encender

    // Player
    #include <Process.h>

#define NUMPASADAS 5  // Numero de lecturas por led
#define MINSONIDO 25  // Minima intensidad de sonido
#define MAXSONIDO 125 // Maxima intensidad de sonido

const int primerLED = 3;  // Primer led de la cadena de leds
const int ultimoLED = 12; // Ultimo led de la cadena de leds
    
    // Player
    const int buttonPin = 2;
    const int ledPin =  13;

int leds;
int pasadas[NUMPASADAS]; // Array para la intensidad de los leds
int index = 0;
int total = 0;
int media = 0;
int sonido = 0;

    // Player
    int buttonState = 0;
    Process p;

// Funcion setup (obligaotria)
// Se ejecuta una sola vez, cuando Arduino se enciende. La usamos para inicializar los pins y las lecturas.
// Configuramos los pins digitales como Outputs (off) con pinmode() y 
// las lecturas en el rango de la variable NUMPASADAS las inicializamos a 0 a la espera de sonido por el micro
void setup() {

    // Player
    Bridge.begin();
    pinMode(ledPin, OUTPUT);      
    pinMode(buttonPin, INPUT);     
  
    for (int r = 0; r < NUMPASADAS; r++) {
        pasadas[r] = 0;
    }
    for (int p = primerLED; p <= ultimoLED; p++) {
        pinMode(p, OUTPUT);
    }
    leds = (ultimoLED - primerLED) + 1;

    // Player
    Serial.begin(57600);
}

// Funcion loop (obligatoria).
// Se ejecuta constantemente despues de setup (). 
// Es donde controlamos los voltajes de los inputs, pasando los outputs de on a off.
void loop() {

    // Player
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {     
      
      digitalWrite(ledPin, HIGH);  
      p.runShellCommand("madplay /mnt/sd/THX.mp3");
      while(p.running());  
      Serial.println("it works!");
      
    } else {
      
      // Vumetro
      digitalWrite(ledPin, LOW); 

      total -= pasadas[index]; // El valor anterior se resta, de esta forma total representa la diferencia con respecto al valor anterior
      pasadas[index] = analogRead(0); // Guardamos en pasadas lo que recibe de A0 analogico. Devolvera entre 0 y 1023
      total += pasadas[index]; // El valor leido se acumula en total
      index++;
  
      if (index >= NUMPASADAS) { //Si llegamos al final de numpasadas, ponemos index a 0 y paramos de guardar señal de A0 en array
         index = 0;
      }
  
      // Sacamos el valor absoluto de la media y aplicamos un corrector para centrar el valor de 0 (silencio) dentro del rango MINSONIDO y MAXSONIDO
      media = abs((total / NUMPASADAS) - 318);
      // La funcion map aplica una regla de proporcionalidad transformando un valor entre MINSONIDO y MAXSONIDO en un valor entre 0 y leds
      sonido = map(media, MINSONIDO, MAXSONIDO, 0, leds); 
  
      for (int ledON = ultimoLED; ledON > (ultimoLED - sonido); ledON--) { // Encendemos leds 
          digitalWrite(ledON, HIGH);
      }
  
      for (int ledOFF = (ultimoLED - sonido); ledOFF >= primerLED; ledOFF--) { // No encendemos leds
          digitalWrite(ledOFF, LOW);
      }
  
      /*  Para invertir el sentido de los led ó bien, girar el Arduino usar este grupo de sentencias en lugar del anterior
          for (int ledON = firstLED; ledON < (firstLED + sound); ledON++) {
              digitalWrite(ledON, HIGH);
          }
      
          for (int ledOFF = (firstLED + sound); ledOFF <= lastLED; ledOFF++) {
              digitalWrite(ledOFF, LOW);
          }
      */
  }
}
