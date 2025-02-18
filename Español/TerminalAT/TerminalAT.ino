/* Autor: Ernesto Tolocka (profe Tolocka)
   Fecha creación: 18-2-2025
   Descripción: Envía y recibe comandos AT a y desde el BW16.
   Licencia: MIT
*/

// Define los pines RX y TX del segundo puerto serie
#define Serial2_RX 5  // RX
#define Serial2_TX 4  // TX

void setup() {

  Serial2.setRX(Serial2_RX);  // Pin RX del segundo puerto
  Serial2.setTX(Serial2_TX);  // Pin TX del segundo puerto
  Serial2.begin(115200);     // Inicializar segundo puerto a 115200
 
  Serial.begin(115200);      // Inicializa puerto principal a 115200

}

void loop() {
 
  char dato;
  if (Serial2.available()) {           //Llega algo del módulo?
    dato=Serial2.read();                //Leer lo que llegó
    Serial.write(dato);                 //Sacarlo al monitor
  }

  if (Serial.available ()) {           //Llega algo del monitor?
    dato=Serial.read();                 //Leer lo que llegó
    Serial2.write(dato);                //Sacarlo al módulo
  }       

}