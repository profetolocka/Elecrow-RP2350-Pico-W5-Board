/* Envía comandos AT de prueba al modulo BW16
  Ejemplo adaptado de la Wiki de Elecrow
*/

// Define los pines RX y TX del segundo puerto serie
#define Serial2_RX 5  // RX
#define Serial2_TX 4  // TX

// Iniciaizar el segundo puerto serie
void UART1_Init()
{
  Serial2.setRX(Serial2_RX);  // Pin RX del segundo puerto
  Serial2.setTX(Serial2_TX);  // Pin TX del segundo puerto
  Serial2.begin(115200);     // Inicializar segundo puerto a 115200
  delay(1000);  
}

// Inicializa el puerto serie principal y el segundo
void setup()
{
  Serial.begin(115200);      // Inicializa puerto principal a 115200
  UART1_Init();              // Inicializa segundo puerto
}

// Corre el test
void loop()
{
  UART1_test();
}

// Funcion de Test de comandos AT
void UART1_test()
{
  Serial2.println("AT");
  delay(500);
  while (Serial2.available())  // Comprueba si hay datos
  {
     Serial.write(Serial2.read());  // Escribe el dato recibido al puerto serie principal
  }
  Serial2.println("AT+GMR");
  delay(500);
  while (Serial2.available())  // Comprueba si hay datos
  {
     Serial.write(Serial2.read());  // Escribe el dato recibido al puerto serie principal
  }
  Serial.println("");
  delay(500);
}
