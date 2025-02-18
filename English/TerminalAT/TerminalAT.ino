/* 
   Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: Feb-18-2025
   Description: Sends and receives AT commands to and from the BW16.
   License: MIT
*/

// Define the RX and TX pins for the second serial port
#define Serial2_RX 5  // RX
#define Serial2_TX 4  // TX

void setup() {

  Serial2.setRX(Serial2_RX);  // RX pin for the second port
  Serial2.setTX(Serial2_TX);  // TX pin for the second port
  Serial2.begin(115200);     // Initialize second port at 115200
  
  Serial.begin(115200);      // Initialize main port at 115200

}

void loop() {
 
  char data;
  if (Serial2.available()) {           // Did something arrive from the module?
    data=Serial2.read();                // Read the incoming data
    Serial.write(data);                 // Send it to the monitor
  }

  if (Serial.available ()) {           // Did something arrive from the monitor?
    data=Serial.read();                 // Read the incoming data
    Serial2.write(data);                // Send it to the module
  }       

}