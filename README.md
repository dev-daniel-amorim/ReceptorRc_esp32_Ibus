# Flysky - receptores - Esp32 (PWM, PPM e Ibus)
Tutoriais sobre transmissor RC Flysky - receptores - Esp32 (PWM, PPM e Ibus)

  
| Tutoriais/Título | Descrição/Link Medium | Links/Vídeos YouTube | Links/Códigos fonte |
| --- | --- | --- | --- |
| Lendo todos os CH com Esp32 | [Link para tutorial no Medium](https://medium.com/@dev.daniel.amorim/flysky-entendendo-receptor-ia10b-0b4f2c4c30e8) | --- | [Link código fonte](https://github.com/dev-daniel-amorim/ReceptorRc_esp32_Ibus/blob/main/Receiver_esp32_Ibus.ino) |
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

<hr>

[<< Voltar para página inicial](https://github.com/dev-daniel-amorim)
