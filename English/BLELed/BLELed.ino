/* 
   Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: Feb-18-2025
   Description: Controls the onboard LED via Bluetooth:
     "LED=ON" = Turns the LED on
     "LED=OFF" = Turns the LED off
   License: MIT
*/

// Define TX and RX pins for Serial2
#define Serial2_RX 5
#define Serial2_TX 4

// Sends an AT command with a timeout
int sendATCommand(String command, int timeout) {
    Serial2.println(command);
    long startTime = millis();
    while (millis() - startTime < timeout * 1000) {
        if (Serial2.available()) {
            String response = Serial2.readString();
            Serial.println (response);
            if (response.indexOf("OK") != -1) {
                return 0; // OK response received
            }
        }
    }
    return 1; // Timeout or incorrect response
}

void setup() {

  // LED output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);

  // Initialize serial ports
  Serial.begin(115200);
  // Set TX and RX pins
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  Serial2.begin(115200);
  delay(5000);

  Serial.println("Configuring Bluetooth...");

  // Ensure Bluetooth is off before configuring
  sendATCommand ("AT+BLEMODE=9",10);

  // Set device name
  sendATCommand ("AT+BLENAME=ProfeTolocka",10);  // Only when OFF
  
  // UUID
  sendATCommand ("AT+BLESERUUID=495353431e4d4bd9ba6123c647249616",10); // Only when OFF

  // Activate Bluetooth in SLAVE mode
  sendATCommand ("AT+BLEMODE=0",10); 

  // Advertising is enabled by default

  Serial.println("Bluetooth ready! Waiting for connection...");

  Serial2.flush();
}

void loop() {
    
    // Receive data from Bluetooth and send it to the Serial Monitor
    if (Serial2.available()) {
        String data = Serial2.readString();
        Serial.print("Received via BT: ");
        Serial.println(data);
        if (data.indexOf("LED=ON") != -1) {          
          Serial.println ("Turning LED ON");
            digitalWrite (LED_BUILTIN, HIGH);

        }
        if (data.indexOf("LED=OFF") != -1) {          
          Serial.println ("Turning LED OFF");
            digitalWrite (LED_BUILTIN, LOW);

        }
    }
}