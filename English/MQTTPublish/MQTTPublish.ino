// Define pines de TX y RX para Serial2
#define Serial2_RX 5
#define Serial2_TX 4

// Define el comando para el modo de trabajo AP+STA
#define SET_WIFI_MODE  "AT+WMODE=1,1"

// Define el comando para conectar
// Reemplaza SSID y PASSW por el nombre de tu red y tu contraseña 
#define SET_WIFI_SSID_PASSWORD  "AT+WJAP=\"LosToloNetwork\",\"performance15\""

// Define comandos para MQTT
// Dirección del brokrer
#define SET_MQTT_URL "AT+MQTT=1,broker.emqx.io"
// Número de puerto
#define SET_MQTT_PORT "AT+MQTT=2,1883"
// Método de conexión
#define SET_MQTT_METHOD  "AT+MQTT=3,1"
// Identificador del cliente (Client ID)
#define SET_MQTT_CLIENT_ID  "AT+MQTT=4,MiPicoW5"
// Conexión
#define SET_MQTT_CONNECT  "AT+MQTT"
// Publicación
#define PUB_MQTT  "AT+MQTTPUB=PicoW5,0,0,Hola"


// Envía un comando AT con timeout
int sendATCommand(String command, int timeout) {
    Serial.flush();
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
  Serial.begin(9600);
  // Establece pines TX y RX
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  Serial2.begin(115200);
  delay(5000);


  if (!sendATCommand (SET_WIFI_MODE,5)) {   // Fija modo
    Serial.println ("Modo OK");

    if (!sendATCommand (SET_WIFI_SSID_PASSWORD,10)) {  // Conecta
      Serial.println ("Wifi conectado");

       // Conectar al servidor MQTT
      sendATCommand (SET_MQTT_URL,5);
      sendATCommand (SET_MQTT_PORT,5);
      sendATCommand (SET_MQTT_METHOD,5);
      sendATCommand (SET_MQTT_CLIENT_ID,5);
      
      // Conectar
      Serial2.println (SET_MQTT_CONNECT);
      // Esperar la respuesta
      while (!Serial2.available());
      Serial.println(Serial2.readString());
            
    } else {
      Serial.println ("Error al conectar!");
    }

  } else {
    Serial.println ("Modo Error!");
  }

}

void loop() {
// Main code to run repeatedly
 
  //Publicar en topico 
  Serial2.println (PUB_MQTT);
  // Esperar la respuesta
  while (!Serial2.available());
  Serial.println(Serial2.readString());

  delay (5000);

}