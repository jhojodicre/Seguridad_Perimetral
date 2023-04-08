//1. Librerias.
  //- 1.1 Librerias
    //****************************
    #include <SPI.h>
    #include <LoRa.h>

//2. Definicion de Pinout
  //****************************
  //      Las Etiquetas para los pinout son los que comienzan con GPIO
  //      Es decir, si queremos activar la salida 1, tenemos que buscar la referencia GPIO 1, Pero solomante Escribir 1 sin "GPIO"
  //      NO tomar como referencia las etiquetas D1.
  //- 2.1 Definicion de etiquetas para las Entradas.
    #define PB_ENTER 0
 
  //- 2.2 Definicion de etiquetas para las Salidas.
   #define LED_azul 2               // Led Por defecto embebido con la Placa GPIO 2 "D4"
   // #define xxxxx 3
   // #define xxxxx 4
   // #define xxxxx 5

  //- 2.3 Modulo de comunicaion rfm95
   #define RFM95_CS 15
   #define RFM95_RST 16
   #define RFM95_INT 5
   
  //- 2.4. Constantes
   //****************************
   #define RF95_FREQ 915.0
 
//3. Variables Globales.
  //****************************
  //-3.1 Variables para las Interrupciones
    String inputString;                     // Buffer recepcion Serial.
    volatile  byte  Hola_1=0;
    volatile  bool stringComplete= false;   // Flag: mensaje Serial Recibido completo.
  //-3.2 Variables Globales para Las Funciones.
    bool inicio=true;             // Habilitar mensaje de inicio por unica vez
    String funtion_Mode;          // Tipo de funcion para ejecutar.
    String funtion_Number;        // Numero de funcion a EJECUTAR.
    String funtion_Parmeter1;     // Parametro 1 de la Funcion;
    String funtion_Parmeter2;     // Parametro 2 de la Funcion;
    bool codified_funtion=false;  // Notifica que la funcion ha sido codificada
  //-3.3 Variables para RF95
    int16_t packetnum = 0;  // packet counter, we increment per xmission
    unsigned int placa; // placa en el perimetro.
    unsigned int zona;  // Zona del perimetro.
    char radiopacket[32] = "012345 23456789 1   ";
//4. Instancias de Clases de Librerias Incluidas.
  //-4.1 Intancia de RF95W.
   //RH_RF95 rf95(RFM95_CS, RFM95_INT);
  //  RH_RF95 rf95;

//5. Funciones ISR.
  //-5.1 ISR Serial
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
  //1. Configuracion de Puertos
    //****************************
    //-1.1 Configuracion de Salidas:
      pinMode(LED_azul, OUTPUT);
      pinMode(RFM95_RST, OUTPUT);
    //-1.2 Configuracion de Entradas
      //****************************
  //2. Condiciones Iniciales.
    //-2.1 Estado de Salidas.
      digitalWrite(LED_azul, HIGH);
      digitalWrite(RFM95_RST, HIGH);
    //-2.2 Valores y Espacios de Variables
      inputString.reserve(200);         // reserve 200 bytes for the inputString:
  //3. Configuracion de Perifericos:
    //-3.1 Initialize serial communication at 9600 bits per second:
      Serial.begin(9600);
      delay(10);
    //-3.2 Interrupciones Habilitadas.
      //interrupts ();
  //4. Sitema Minimo Configurado.
    Serial.println("Sistema Minimo Configurado");
  //5. Configuracion de DEVICE externos
  //-5.1 Configuracion RF95
    //-5.1.1 RESET.
      // digitalWrite(RFM95_RST, LOW);
      // delay(10);
      // digitalWrite(RFM95_RST, HIGH);
      // delay(10);
    //-5.1.2 INIT. RF95
      // while (!rf95.init()) {                      // 3 Iniciamos el Modulo RADIO
      //   Serial.println("LoRa radio init failed");
      //   while (1);
      // }
      // Serial.println("LoRa radio init OK!");      // ____DEBUG.

    //-5.1.3 SET FRECUENCY
      // if (!rf95.setFrequency(RF95_FREQ)) {        // 4. Establecemos La frecuencia.
      //   Serial.println("setFrequency failed");
      //   while (1);
      // }
      // Serial.print("Set Freq to: ");              // ____DEBUG.  
      // Serial.println(RF95_FREQ);

    //-5.1.4 SET POWER TRANSMIT
      // rf95.setTxPower(23, false);
        Serial.println("LoRa Sender");
        LoRa.setPins(15, 16, 5);
        if (!LoRa.begin(915E6)) {
          Serial.println("Starting LoRa failed!");
          while (1);
        }

}
void loop() {
  //1. Mensaje de Bienvenida Para Comprobar el Sistema minimo de Funcionamiento.
    while (inicio){
      welcome();
      led_Monitor(2);
    }
  //2. Decodificar Funcion
    if(stringComplete){
      decodificar_solicitud();
    }
  //3. Ejecutar Funcion
    if(codified_funtion){
      ejecutar_solicitud();
      // 3.1 Desactivar Banderas.
      codified_funtion=false;
    }
}
//    Funciones de Logic interna del Micro.
  void welcome(){
    // Deshabilitamos Banderas
      inicio=false;
      Serial.println("Comenzamos el Programa");
      Serial.println("Esperamos recibir un Dato");
      Serial.println("ESP8266 MASTER CONFIGURADO");
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
    //Deshabilitamos Banderas
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
//    Funciones de dispositivo externos.
  // void f3_rf95(){
  //   Serial.println("Sending to rf95_server");     // ___DEBUG
  //   //char radiopacket[32] = "HOLA_123            ";
  //   //itoa(packetnum++, radiopacket+13, 10);                // 7. Convertimos una cadena a nuemeros de base 10 en caracter.
  //   uint8_t radiopacket[]="hola";
  //   //Serial.print("Sending ");
  //   //Serial.println(radiopacket);
  //   //radiopacket[31] = 0;
  //   Serial.println("Sending..."); 
  //   //delay(10);
  // //}
  //void rf95_enviar(){
    // rf95.send(radiopacket, sizeof(radiopacket));
    // digitalWrite(LED_azul, HIGH);
    // Serial.println("Waiting for packet to complete...");
    // delay(10);
    // rf95.waitPacketSent();
  //}
  //void rf95_recibir(){
    // Now wait for a reply
  //   uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  //   uint8_t len = sizeof(buf);

  //   Serial.println("Waiting for reply..."); 
  //   delay(10);
  //   if (rf95.waitAvailableTimeout(1000))
  //   { 
  //     // Should be a reply message for us now   
  //     if (rf95.recv(buf, &len))
  //    {
  //       Serial.print("Got reply: ");
  //       Serial.println((char*)buf);
  //       Serial.print("RSSI: ");
  //       Serial.println(rf95.lastRssi(), DEC);    
  //     }
  //     else
  //     {
  //       Serial.println("Receive failed");
  //     }
  //   }
  //   else
  //   {
  //     Serial.println("No reply, is there a listener around?");
  //   }

  //   delay(1000);
  //   digitalWrite(LED_azul, LOW);
  // }
//    Funciones Seleccionadas para Ejecutar.
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
  void f2_serial_Enviar(int par1){
    // Deshabilitamos Banderas
    int counter=par1;
    Serial.print("Sending packet: ");
    Serial.println(counter);

    // send packet
    LoRa.beginPacket();
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket();

    // counter++;

    delay(5000);
  }
//    Ultima Funcion
  void ejecutar_solicitud(){
    // Deshabilitamos Banderas
    int x1=funtion_Parmeter1.toInt();
    int x2=funtion_Parmeter2.toInt();
    if (funtion_Number=="1"){
      Serial.println("funion Nº1");
      f1_Destellos(x1,x2);
    }
    if (funtion_Number=="2"){
      Serial.println("funion Nº2");
      f2_serial_Enviar(x2);
    }
    if (funtion_Number=="3"){
      Serial.println("funion Nº3");
      //f3_rf95();
    }
    else{
      Serial.println("Ninguna Funcion");
    }
      
  }