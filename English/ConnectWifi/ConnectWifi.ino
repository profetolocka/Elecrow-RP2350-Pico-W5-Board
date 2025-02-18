/* 
   Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: Feb-18-2025
   Description: Connects to a WiFi network
   License: MIT
*/

// Define TX and RX pins for Serial2
#define Serial2_RX 5
#define Serial2_TX 4

// Define the command for STA mode
#define SET_WIFI_MODE  "AT+WMODE=1,1"
// Define the command to connect
// Replace SSID and PASSW with your network name and password
#define SET_WIFI_SSID_PASSWORD  "AT+WJAP=\"SSID\",\"PASSW\""

// Wait until buffers are empty
void clearSerial() {
  while (Serial2.read() >= 0);
  while (Serial.read() >= 0);
}

// Send an AT command with a timeout
int sendATCommand(String command, int timeout) {
    clearSerial();
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
  Serial.begin(115200);
  // Set TX and RX pins
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  Serial2.begin(115200);
  delay(5000);

  if (!sendATCommand (SET_WIFI_MODE,5)) {   // Set mode
    Serial.println ("Mode OK");

    if (!sendATCommand (SET_WIFI_SSID_PASSWORD,10)) {  // Connect
      Serial.println ("WiFi connected");
    } else {
      Serial.println ("Connection error!");
    }

  } else {
    Serial.println ("Mode error!");
  }

}

void loop() {
// Main code to run repeatedly

}

