
/**************************************************************************************************
DESENVOLVIDO, MODIFICADO E ATUALIZADO POR:
DESENVOLVEDOR: DANIEL SÃ
PROFISSÃO: ENG. DE COMPUTACAO
YOUTUBE:

SOBRE ESTE CÓDIGO:
  CONECTANDO CONTROLE RC FLYSKY DE 10 CANAIS COM ESP32

CANAIS DO CONTROLE RC (MINHAS CONFIGURAÇÕES NO CONTROLE):
  - CH1 - ANALOGICO DIREITO ESQUERDA/DIREITA QUE VAI DE 1000 A 2000
  - CH2 - ANALOGICO DIREITO COMA/BAIXO QUE VAI DE 1000 A 2000
  - CH5 - DIGITAL VALOR ENTRE 0 E 1

DICA:
  - O SERVO NAO GIRA 180, GIRA APENAS 90 GRAUS, VEJA ESTE VIDEO COMO ALTERAR: https://www.youtube.com/watch?v=Qr4TAQXisO8

***************************************************************************************************/
 // Definição das conexões de entrada
#define CH1 14
#define CH2 25
#define CH5 26
 
// Vaiáveis analógicas
int valorCH1;
int valorCH2;

// Variável boleana 
bool valorCH5;

//Essa função readChannel tem o objetivo de ler um valor de um canal de entrada 
//(geralmente de um sensor ou controle, como um potenciômetro, servomotor, ou outro dispositivo), 
//ajustar o valor lido dentro de um intervalo especificado, e garantir que o valor retornado esteja dentro dos limites estabelecidos.
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
  bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup(){

  Serial.begin(115200);
  
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH5, INPUT);
}
 
 
void loop() {
  
  // converte os valores do controle RC de 1000 a 2000 para a faixa de 0 a 255 para um servo por exemplo
  valorCH1 = readChannel(CH1, 0, 255, 0);
  valorCH2 = readChannel(CH2, 0, 255, 0);

  valorCH5 = readSwitch(CH5, false);
  
  // Imprime na serial
  Serial.print("Ch1: ");
  Serial.print(valorCH1);
  Serial.print(" | Ch2: ");
  Serial.print(valorCH2);
  Serial.print(" | CH5: ");
  Serial.println(valorCH5);
  
  delay(500);
}
