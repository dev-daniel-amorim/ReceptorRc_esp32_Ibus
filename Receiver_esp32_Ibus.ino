#include <IBusBM.h>

IBusBM ibus;

#define IBUS_RX_PIN 16  // Pino RX do ESP32 (conectado ao sinal do iBUS)

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, IBUS_RX_PIN, -1);  // Apenas RX usado

  ibus.begin(Serial2);  // Inicializa o iBUS
}

void loop() {
  for (int ch = 0; ch < 10; ch++) {
    Serial.print("CH"); Serial.print(ch + 1); Serial.print(": ");
    Serial.print(ibus.readChannel(ch)); Serial.print("\t");
  }
  Serial.println();
  delay(100);
}
