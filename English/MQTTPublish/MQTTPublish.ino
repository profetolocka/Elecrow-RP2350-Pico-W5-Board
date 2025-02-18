/* 
   Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: Feb-18-2025
   Description: Publishes to an MQTT server
   License: MIT
*/

// Define TX and RX pins for Serial2
#define Serial2_RX 5
#define Serial2_TX 4

// Define the command for AP+STA mode
#define SET_WIFI_MODE  "AT+WMODE=1,1"

// Define the command to connect
// Replace SSID and PASSW with your network name and password
#define SET_WIFI_SSID_PASSWORD  "AT+WJAP=\"LosToloNetwork\",\"performance15\""

// Define MQTT commands
// Broker address
#define SET_MQTT_URL "AT+MQTT=1,broker.emqx.io"
// Port number
#define SET_MQTT_PORT "AT+MQTT=2,1883"
// Connection method
#define SET_MQTT_METHOD  "AT+MQTT=3,1"
// Client ID
#define SET_MQTT_CLIENT_ID  "AT+MQTT=4,MyPicoW5"
// Connect command
#define SET_MQTT_CONNECT  "AT+MQTT"
// Publish command
#define PUB_MQTT  "AT+MQTTPUB=PicoW5,0,0,Hello"

// Sends an AT command with a timeout
int sendATCommand(String command, int timeout) {
    Serial.flush();
    Serial2.println(command);
    long startTime = millis();
    while (millis() - startTime < timeout * 1000) {
        if (Serial2.available()) {
            String response = Serial2.readString();
            if (response.indexOf("OK") != -1) {
                return 0; // OK response received
            }
        }
    }
    return 1; // Timeout or incorrect response
}

void setup() {

  // Initialize serial ports
  Serial.begin(9600);
  // Set TX and RX pins
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  Serial2.begin(115200);
  delay(5000);

  if (!sendATCommand (SET_WIFI_MODE,5)) {   // Set mode
    Serial.println ("Mode OK");

    if (!sendATCommand (SET_WIFI_SSID_PASSWORD,10)) {  // Connect
      Serial.println ("WiFi connected");

      // Connect to MQTT server
      sendATCommand (SET_MQTT_URL,5);
      sendATCommand (SET_MQTT_PORT,5);
      sendATCommand (SET_MQTT_METHOD,5);
      sendATCommand (SET_MQTT_CLIENT_ID,5);
      
      // Connect
      Serial2.println (SET_MQTT_CONNECT);
      // Wait for response
      while (!Serial2.available());
      Serial.println(Serial2.readString());
            
    } else {
      Serial.println ("Connection error!");
    }

  } else {
    Serial.println ("Mode error!");
  }

}

void loop() {
// Main code to run repeatedly
 
  // Publish to topic 
  Serial2.println (PUB_MQTT);
  // Wait for response
  while (!Serial2.available());
  Serial.println(Serial2.readString());

  delay (5000);

}
