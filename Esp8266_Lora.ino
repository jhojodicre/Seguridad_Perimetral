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
  String inputString;                     // Buffer recepcion Serial.
  volatile  byte  Hola_1=0;
  volatile  bool stringComplete= false;   // Flag: mensaje Serial Recibido completo.

  //    -3.2 Variables Globales para Las Funciones.
  bool inicio=true;             // Habilitar mensaje de inicio por unica vez
  String funtion_Mode;          // Tipo de funcion para ejecutar.
  String funtion_Number;        // Numero de funcion a EJECUTAR.
  String funtion_Parmeter1;     // Parametro 1 de la Funcion;
  String funtion_Parmeter2;     // Parametro 2 de la Funcion;
  bool codified_funtion=false;  // Notifica que la funcion ha sido codificada

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
      codified_funtion=false;
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
    welcome();
    led_Monitor(2);
  }
  if(stringComplete){
    decodificar_solicitud();
  }
  if(codified_funtion){
    ejecutar_solicitud();
    codified_funtion=false;
  }
}
void welcome(){
  // Deshabilitamos Banderas
    inicio=false;
    Serial.println("Comenzamos el Programa");
    Serial.println("Esperamos recibir un Dato");
}
void led_Monitor(int repeticiones){
  // Deshabilitamos Banderas
  int repetir=repeticiones;
  for (int encender=0; encender<=repetir; ++encender){
    digitalWrite(LED_azul, LOW);   // Led ON.
    delay(500);                    // pausa 1 seg.
    digitalWrite(LED_azul, HIGH);    // Led OFF.
    delay(500);                    // pausa 1 seg.
  }
}
void decodificar_solicitud(){
  // Deshabilitamos Banderas
  stringComplete=false;
  codified_funtion=true;
  Serial.println(inputString);         // Pureba de Comunicacion Serial.
  funtion_Mode=inputString.substring(0,1);
  funtion_Number=inputString.substring(1,2);
  funtion_Parmeter1=inputString.substring(2,3);
  funtion_Parmeter2=inputString.substring(3,4);
  inputString="";
  Serial.println("funcion: " + funtion_Mode);
  Serial.println("Numero: " + funtion_Number);
  Serial.println("Parametro1: " + funtion_Parmeter1);
  Serial.println("Parametro2: " + funtion_Parmeter2+ "\n");
  //Serial.println("Numero de funcion: ")

}
void serial_Enviar(){
  // Deshabilitamos Banderas
  Serial.println("hola");         // Pureba de Comunicacion Serial.
}

void f1_Destellos (int repeticiones, int tiempo){
  int veces=repeticiones;
  int retardo=tiempo*100;
  Serial.println("Ejecutando F1.. \n");
  for(int repetir=0; repetir<veces; ++repetir){
    delay(retardo);                  // pausa 1 seg.
    digitalWrite(LED_azul, LOW);     // Led ON.
    delay(retardo);                  // pausa 1 seg.
    digitalWrite(LED_azul, HIGH);    // Led OFF.
  }
}

void ejecutar_solicitud(){
  // Deshabilitamos Banderas
  if (funtion_Number=="1"){
    int x1=funtion_Parmeter1.toInt();
    int x2=funtion_Parmeter2.toInt();
    Serial.println("funion Nº1");
    f1_Destellos(x1,x2);
  }
  if (funtion_Number=="2"){
    Serial.println("funion Nº2");
  }
  if (funtion_Number=="3"){
    Serial.println("funion Nº3");
  }
}