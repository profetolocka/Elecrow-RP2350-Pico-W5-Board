/* 
   Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: Feb-18-2025
   Description: Connects to an API using HTTP GET
   License: MIT
*/

// Define TX and RX pins for Serial2
#define Serial2_RX 5
#define Serial2_TX 4

// Define the command for AP+STA mode
#define SET_WIFI_MODE           "AT+WMODE=3,1"
// Define the command to connect
// Replace SSID and PASSW with your network name and password
#define SET_WIFI_SSID_PASSWORD  "AT+WJAP=\"SSID\",\"PASSW\""
// Define the command to make an HTTP request with the format required by the API
#define GET_HTTP_REQ  "AT+HTTPCLIENTLINE=1,2,\"application/x-www-form-urlencoded\",\"api.open-meteo.com\",80,\"/v1/forecast?latitude=-31.137&longitude=-64.296&current=temperature_2m\""

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
      
      // Send HTTP request
      Serial2.println (GET_HTTP_REQ);
      // Wait for the response
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

}

