// Define pines de TX y RX para Serial2
#define Serial2_RX 5
#define Serial2_TX 4


// Define el comando para el modo de trabajo STA
#define SET_WIFI_MODE  "AT+WMODE=1,1"
// Define el comando para conectar
// Reemplaza SSID y PASSW por el nombre de tu red y tu contraseña 
#define SET_WIFI_SSID_PASSWORD  "AT+WJAP=\"LosToloNetwork-5G\",\"performance15\""

// Espera a que no haya nada en los buffers
void clearSerial() {
  while (Serial2.read() >= 0);
  while (Serial.read() >= 0);
}

// Envía un comando AT con timeout
int sendATCommand(String command, int timeout) {
    clearSerial();
    Serial2.println(command);
    long startTime = millis();
    while (millis() - startTime < timeout * 1000) {
        if (Serial2.available()) {
            String response = Serial2.readString();
            if (response.indexOf("OK") != -1) {
                return 0; // Respuesta OK recibida
            }
        }
    }
    return 1; // Timeout o respuesta incorrecta
}

void setup() {

  // Inicializa los puertos serie
  Serial.begin(115200);
  // Establece pines TX y RX
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  Serial2.begin(115200);
  delay(5000);


  if (!sendATCommand (SET_WIFI_MODE,5)) {   // Fija modo
    Serial.println ("Modo OK");

    if (!sendATCommand (SET_WIFI_SSID_PASSWORD,10)) {  // Conecta
      Serial.println ("Wifi conectado");
    } else {
      Serial.println ("Error al conectar!");
    }

  } else {
    Serial.println ("Modo Error!");
  }


}

void loop() {
// Main code to run repeatedly

}

