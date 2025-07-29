/***************************************************************************************************
DESENVOLVIDO POR:
DESENVOLVEDOR: DANIEL SÃ
PROFISSÃO: ENG. DE COMPUTACAO
YOUTUBE:

FUNCIONALIDADES DESTA VERSÃO:
LER NA PORTA SERIAL 1 DO ESP32 TODOS OS CANAIS DO RECEPTOR FS-IA10B COM TRANSMISSOR FLYSKY 

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

#define IBUS_BUFFSIZE 32
#define IBUS_MAXCHANNELS 10

HardwareSerial FlySkySerial(1);  // UART1 no ESP32

uint8_t ibus[IBUS_BUFFSIZE] = {0};
uint8_t ibusIndex = 0;
uint16_t rcValue[IBUS_MAXCHANNELS];

void setup() {
  Serial.begin(115200);
  delay(500);

  // RX em GPIO16, TX não usado
  FlySkySerial.begin(115200, SERIAL_8N1, 16, -1);

  Serial.println("IBUS iniciado. Lendo canais...");
}

void loop() {
  while (FlySkySerial.available()) {
    uint8_t val = FlySkySerial.read();

    // Verifica início do pacote IBUS (0x20 0x40)
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

      // Extrai valores dos canais (2 bytes por canal)
      for (int i = 0; i < IBUS_MAXCHANNELS; i++) {
        int low = 2 + i * 2;
        int high = 3 + i * 2;
        rcValue[i] = (ibus[high] << 8) | ibus[low];
      }

      // Processa canais
      for (int i = 0; i < IBUS_MAXCHANNELS; i++) {
        int raw = rcValue[i];
        int output = 0;

        // Tratamento especial para ler portas de 0 a 255, portas de 2 estados (0 e 1) e portas triestados (0, 1 e -1)
        if (i == 4 || i == 5 || i == 9) {  // Canais 5, 6 e 10 (índices 4, 5, 9)
          output = (raw > 1500) ? 1 : 0;
        } else if (i == 8) {  // Canal 9 (índice 8): triestado
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
      }

      Serial.println();
    }
  }
}

