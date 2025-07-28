/***************************************************************************************************
DESENVOLVIDO POR:
DESENVOLVEDOR: DANIEL SÃ
PROFISSÃO: ENG. DE COMPUTACAO
YOUTUBE:

INFORMAÇÕES IMPORTANTES:
  - CÓDIGO PARA LER DADOS DO RECEPTOR FS-IA10B COM ESP32 PROTOCOLO IBUS
  - O ESP32 SO PODE RECEBER 3V3 NAS SUAS PORTAS E O RECEPTOR ENVIA 5V NO TX, CUIDADO USE DIVISOR DE TENSÃO PARA NAO QUEIMAR O ESP32

DADOS DOS CANAIS DO TRANSMISSOR (MINHAS CONFIGURAÇÕES):
  - CH1 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 0 A 255 (CONVERTIDO COM MAP)
  - CH2 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 0 A 255 (CONVERTIDO COM MAP)
  - CH3 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 0 A 255 (CONVERTIDO COM MAP)
  - CH4 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 0 A 255 (CONVERTIDO COM MAP)
  - CH5 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 1 OU O  (CONVERTIDO COM MAP)  
  - CH6 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 1 OU O  (CONVERTIDO COM MAP)  
  - CH7 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 0 A 255 (CONVERTIDO COM MAP)
  - CH8 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) 0 A 255 (CONVERTIDO COM MAP)
  - CH9 - 1000 A 2000 (PADRÃO DO TRANSMISSOR) TRIESTADOS -1, 0 OU 1  (CONVERTIDO COM MAP)
  - CH10- 1000 A 2000 (PADRÃO DO TRANSMISSOR) 1 OU O  (CONVERTIDO COM MAP)
*****************************************************************************************************/

#include <HardwareSerial.h>
#include <ESP32Servo.h>   // Servo para ESP32

#define IBUS_BUFFSIZE 32
#define IBUS_MAXCHANNELS 10

HardwareSerial FlySkySerial(1);  // UART1

uint8_t ibus[IBUS_BUFFSIZE] = {0};
uint8_t ibusIndex = 0;
uint16_t rcValue[IBUS_MAXCHANNELS];

#define SERVO_PIN 13
Servo servoDirecao;  // Objeto do servo

void setup() {
  Serial.begin(115200);
  delay(500);

  // Inicia UART para iBUS (RX no GPIO16)
  FlySkySerial.begin(115200, SERIAL_8N1, 16, -1);
  Serial.println("IBUS iniciado. Lendo canais...");

  // Anexa o servo
  servoDirecao.setPeriodHertz(50);  // Frequência típica de servo
  servoDirecao.attach(SERVO_PIN, 1000, 2000);  // Min e max pulse (µs)
}

void loop() {
  while (FlySkySerial.available()) {
    uint8_t val = FlySkySerial.read();

    if (ibusIndex == 0 && val != 0x20) {
      ibusIndex = 0;
      return;
    }

    if (ibusIndex == 1 && val != 0x40) {
      ibusIndex = 0;
      return;
    }

    if (ibusIndex < IBUS_BUFFSIZE) {
      ibus[ibusIndex++] = val;
    }

    if (ibusIndex == IBUS_BUFFSIZE) {
      ibusIndex = 0;
      // ABAIXO MAPEIA OS CANAIS, ALGUNS SAO DE 0 A 255, OUTROS 0 E 1 E OUTROS TRIESTADOS 0, 1 E -1
      for (int i = 0; i < IBUS_MAXCHANNELS; i++) {
        int low = 2 + i * 2;
        int high = 3 + i * 2;
        rcValue[i] = (ibus[high] << 8) | ibus[low];
      }

      for (int i = 0; i < IBUS_MAXCHANNELS; i++) {
        int raw = rcValue[i];
        int output = 0;

        if (i == 4 || i == 5 || i == 9) {
          output = (raw > 1500) ? 1 : 0;
        } else if (i == 8) {
          if (raw < 1200) output = -1;
          else if (raw > 1800) output = 1;
          else output = 0;
        } else {
          output = constrain(map(raw, 1000, 2000, 0, 255), 0, 255);
        }

        Serial.print("CH");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(output);
        Serial.print("\t");

        // === SERVO CONTROLADO PELO CH1 ===
        if (i == 0) {
          // PARA DIMINUIR O ANGULO DE ATAQUE DO SERVO AUMENTE O "0" E DIMINUA O "180" NA MESMA PROPORÇÃO
          // EXEMPLO, AUMENTAR E DIMINUIR 20 GRAUS -> map(raw, 1000, 2000, **20, **160) **ONDE MUDAR
          int angulo = map(raw, 1000, 2000, 0, 180);  // ou writeMicroseconds(raw);
          servoDirecao.write(angulo);
        }
      }

      Serial.println();
    }
  }
}
