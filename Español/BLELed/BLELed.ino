/* Autor: Ernesto Tolocka (profe Tolocka)
   Fecha creación: 18-2-2025
   Descripción: Controla el led incorporado a través de BT:
     "LED=ON" = Prende el led
    "LED=OFF" = Apaga el led
   Licencia: MIT
*/


// Define pines de TX y RX para Serial2
#define Serial2_RX 5
#define Serial2_TX 4

// Envía un comando AT con timeout
int sendATCommand(String command, int timeout) {
    //clearSerial();
    Serial2.println(command);
    long startTime = millis();
    while (millis() - startTime < timeout * 1000) {
        if (Serial2.available()) {
            String response = Serial2.readString();
            Serial.println (response);
            if (response.indexOf("OK") != -1) {
                return 0; // Respuesta OK recibida
            }
        }
    }
    return 1; // Timeout o respuesta incorrecta
}

void setup() {

  //Salida del LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);

  // Inicializa los puertos serie
  Serial.begin(115200);
  // Establece pines TX y RX
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  Serial2.begin(115200);
  delay(5000);

  Serial.println("Configurando Bluetooth...");

  // Asegurar el BT apagado para configurarlo
  sendATCommand ("AT+BLEMODE=9",10);

  // Configurar nombre del dispositivo
  sendATCommand ("AT+BLENAME=ProfeTolocka",10);  //Sólo en OFF
  
  // UUID
  sendATCommand ("AT+BLESERUUID=495353431e4d4bd9ba6123c647249616",10); //Sólo en OFF

  // Activar BT en modo SLAVE
  sendATCommand ("AT+BLEMODE=0",10); 

  //La publicidad está activada por defecto

  Serial.println("Bluetooth listo! Esperando conexión...");

  Serial2.flush();
}

void loop() {
    
    // Recibir datos desde Bluetooth y enviarlos al Monitor Serie
    if (Serial2.available()) {
        String data = Serial2.readString();
        Serial.print("Recibido via BT: ");
        Serial.println(data);
        //Serial.println (strlen(data));
        if (data.indexOf("LED=ON") != -1) {          
          Serial.println ("Prende LED");
            digitalWrite (LED_BUILTIN, HIGH);

        }
        if (data.indexOf("LED=OFF") != -1) {          
          Serial.println ("Apaga LED");
            digitalWrite (LED_BUILTIN, LOW);

        }
    }
}