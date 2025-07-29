# Flysky - receptores - Esp32 (PWM, PPM e Ibus)
Tutoriais sobre transmissor RC Flysky - receptores - Esp32 (PWM, PPM e Ibus)

  
| Tutoriais/Título | Descrição/Link Medium | Links/Vídeos YouTube | Links/Códigos fonte |
| --- | --- | --- | --- |
| iBus - Lendo CHs com Esp32 | [Link para tutorial no Medium](https://medium.com/@dev.daniel.amorim/flysky-entendendo-receptor-ia10b-0b4f2c4c30e8) | --- | [Link código fonte](https://github.com/dev-daniel-amorim/ReceptorRc_esp32_Ibus/blob/main/iBus_com_esp.ino) |
| PWM -Lendo CHs com Esp32 | [Link para tutorial no Medium](https://medium.com/@dev.daniel.amorim/flysky-entendendo-receptor-ia10b-0b4f2c4c30e8) | --- | [Link código fonte](https://github.com/dev-daniel-amorim/ReceptorRc_esp32_Ibus/blob/main/PWM_com_esp.ino) |





<br>

## Lendo dados de um receptor FS-I10B 
Com receptor RC podemos capturar dados do controle RC através de um ESP32 de 3 maneirias diferentes:

PWM: “Pulse Width Modulation”, significa Modulação por Largura de Pulso, mas pra isso precisamos ler um canal por fio ocupando mais portas do esp32 ou ligar diretamente nos servos.

PPM: “Pulse position modulation”, usa somente um fio pra transmitir todos os canais, porém o ESP32 pode ler PPM, mas é mais trabalhoso (precisa decodificar temporização via pulseIn ou interrupt).

Ibus: Protocolo de comunicação, onde podemos receber em um so fio pacotes contendo dados de todos os canais e com checksum, mais fácil pois com esp32 ja temos bibliotecas prontas e capaz de interpretar os pacotes.

## Vamos coletar dados usando protocolo IBUS
Os pinos de comunicação IBUS estão definidos na imagem abaixo:


<p align="center">
  <img src="https://github.com/user-attachments/assets/8ab7aae1-020c-49d2-b010-d35b90e14bb0" width="50%" />
</p>
<br>

Muito cuidado, a saída TX do receptor tem sinal de 5v e a porta RX do esp32 so aceita até 3,3v, para receber dados no esp32 use um divisor de tensão para não queimar seu ESP, abaixo um esquema do divisor:

<p align="center">
  <img src="https://github.com/user-attachments/assets/04521fc8-1cab-4c5d-a10b-1dbb73336521" width="30%" />
</p>
<br>

Basta seguir o esquema elétrico abaixo e compilar o código (iBUS) para o seu esp32 e você verá a mágica acontecendo:

<p align="center">
  <img src="https://github.com/user-attachments/assets/550a8f1d-9b4a-4019-880d-00df04439d4d" width="50%" />
</p>
<br>

## Vamos coletar dados usando PWM
Os pinos de comunicação PWM estão definidos na imagem abaixo, para ligação dos pinos no Esp32 basta usar os pinos definidos no código fonte, mas cuidado, as saídas são 5v, use o divisor para ler no Esp32:

<p align="center">
  <img src="https://github.com/user-attachments/assets/016742c6-47c6-472c-b53b-05a31402c573" width="50%" />
</p>
<br>

Feitas as ligações acima com seu Esp32, basta carregar o códido (PWM) publicado na tabela acima.

<hr>

[<< Voltar para página inicial](https://github.com/dev-daniel-amorim)
