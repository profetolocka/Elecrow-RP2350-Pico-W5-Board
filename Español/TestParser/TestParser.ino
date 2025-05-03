/* 
   Author: Ernesto Tolocka (Profe Tolocka)
   Creation Date: Feb-18-2025
   Description: Connects to a WiFi network
   License: MIT
*/

#include "TinyATCommandParser.h"

// Define TX and RX pins for Serial2
#define Serial2_RX 5
#define Serial2_TX 4

#define SERIAL_BW16 Serial2  // Puerto Serial donde está conectado el BW16
#define DEBUG Serial         // Monitor Serial para depuración

TinyATCommandParser parser;



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

// Callback para manejar la respuesta de AT+CWJAP (Conexión WiFi)
void handleWiFiConnection(const char* command, const char* params) {
    if (params) {
        DEBUG.print("Respuesta de WiFi: ");
        DEBUG.println(params);
        if (strstr(params, "OK")) {
            DEBUG.println("✅ Conectado a WiFi exitosamente.");
        } else if (strstr(params, "FAIL")) {
            DEBUG.println("❌ Error al conectar a WiFi.");
        }
    }
}

// Callback para manejar la respuesta de AT+CIFSR (Dirección IP)
void handleIPResponse(const char* command, const char* params) {
    if (params) {
        DEBUG.print("Dirección IP asignada: ");
        DEBUG.println(params);
    }
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

  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
 
 
    DEBUG.begin(115200);       // Iniciar el monitor serial
    SERIAL_BW16.begin(115200); // Iniciar la comunicación con el BW16


  // Initialize serial ports
  //Serial.begin(115200);
  // Set TX and RX pins
  Serial2.begin(115200);
  delay(5000);

    // Configurar comandos y sus funciones de respuesta
    parser.addCommand("AT+CWJAP", handleWiFiConnection);
    parser.addCommand("AT+CIFSR", handleIPResponse);

    DEBUG.println("Inicializando conexión WiFi...");

    // Enviar comandos al BW16
    SERIAL_BW16.println("AT+CWMODE=1");  // Configurar el modo STA
    delay(500);
    
    SERIAL_BW16.println("AT+CWJAP=\"TuSSID\",\"TuPASSWORD\""); // Conectar a WiFi

}

void loop() {
    // Leer datos desde el BW16 y procesarlos con el parser
    while (SERIAL_BW16.available()) {
        char incomingChar = SERIAL_BW16.read();
        parser.process(incomingChar);
    }
}
