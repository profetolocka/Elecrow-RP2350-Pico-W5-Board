// Define pines de TX y RX para Serial2
#define Serial2_RX 5
#define Serial2_TX 4

void setup() {

 // Inicializa los puertos serie
  Serial.begin(115200);
  // Establece pines TX y RX
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  Serial2.begin(115200);
  delay(5000);

       Serial.println("Configurando Bluetooth en modo clásico...");

    // 1. Configurar modo Bluetooth clásico (SPP)
    Serial2.println("AT+BLEMODE=3");
    delay(100);

    // 2. Habilitar el perfil SPP (Serial Port Profile)
    Serial2.println("AT+SPPEN=1");
    delay(100);

    // 3. Configurar nombre del dispositivo
    Serial2.println("AT+BLENAME=Arduino_BT");
    delay(100);

    // 4. Activar publicidad Bluetooth
    Serial2.println("AT+BLEADVEN=1");
    delay(100);

    Serial.println("Bluetooth clásico listo! Esperando conexión...");
}

void loop() {
    // Recibir datos desde Bluetooth y enviarlos al Monitor Serie
    if (Serial2.available()) {
        String data = BTSerial.readString();
        Serial.print("Recibido via BT: ");
        Serial.println(data);
    }

    // Enviar datos desde el Monitor Serie al Bluetooth
    if (Serial.available()) {
        String msg = Serial.readString();
        Serial2.println(msg);
    }
}