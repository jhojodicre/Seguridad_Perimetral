  //****************************
  //1. Librerias


  //****************************
  //2.  Definicion de Pinout
  //      Las Etiquetas para los pinout son los que comienzan con GPIO
  //      Es decir, si queremos activar la salida 1, tenemos que buscar la referencia GPIO 1, Pero solomante Escribir 1 sin "GPIO"
  //      NO tomar como referencia las etiquetas D1.

  //    - 2.1 Definicion de etiquetas para las Entradas.

  #define PB_ENTER 0

  //    - 2.2 Definicion de etiquetas para las Salidas.
 #define LED_azul 2               // Led Por defecto embebido con la Placa GPIO 2 "D4"

  // #define xxxxx 3
  // #define xxxxx 4
  // #define xxxxx 5


  //****************************
  //3. Constantes



  //****************************
  //3. Variables Globales.

  //   -3.1 Variables para las Interrupciones
  String inputString;
  volatile  byte  Hola_1=0;
  volatile  bool stringComplete= false;

  //    -3.2 Variables Globales para Las Funciones.
  bool inicio=true;

void serialEvent (){
   while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }

  }

}
void setup() {


  //****************************
  //1.  Configuracion de Puertos
  //    1.1 Configuracion de Salidas:
  pinMode(LED_azul, OUTPUT);

  //    1.2 Configuracion de Entradas
  //****************************
  // 2. Configuracion de Perifericos:
  //    - 2.1 Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  //    - 2.2 Interrupciones Habilitadas.
  //interrupts ();

  //2.  Condiciones Iniciales
  digitalWrite(LED_azul, HIGH);
}

void loop() {
  while (inicio){
    inicio=false;
    Serial.println("Comenzamos el Programa");
    Serial.println("Esperamos recibir un Dato");
  }
  if(stringComplete){
    Serial.println(inputString);         // Pureba de Comunicacion Serial.
  }
  

}

void led_Monitor(){
  digitalWrite(LED_azul, HIGH);   // Led ON.
  delay(1000);                    // pausa 1 seg.
  digitalWrite(LED_azul, LOW);    // Led OFF.
  delay(1000);                    // pausa 1 seg.
}

void serial_Enviar(){
  Serial.println("hola");         // Pureba de Comunicacion Serial.
}
