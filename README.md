# Jogo da Memória com Arduino

Este projeto é um **Jogo da Memória** desenvolvido com a plataforma **Arduino**. O objetivo do jogo é ajudar os jogadores a melhorarem suas habilidades de memória, memorizando e reproduzindo uma sequência de luzes e sons que ficam cada vez mais complexas.

## 📦 Componentes Utilizados

- 1x Arduino Uno
- 4x LEDs (vermelho, verde, azul, amarelo)
- 4x Botões Push-button
- 1x Buzzer 
- Resistores 220Ω para os LEDs
- Protoboard e jumpers

## 📐 Circuito

O circuito é composto por quatro LEDs e quatro botões, onde cada LED corresponde a um botão. O jogador deve seguir uma sequência aleatória de LEDs que é mostrada, pressionando os botões correspondentes na mesma ordem.
![Texto alternativo](./Imagem/jogo.png)

### Esquema Básico de Conexões:


## 🕹️ Como Jogar

1. Quando o jogo começar, o Arduino acenderá uma sequência de LEDs.
2. O jogador deve pressionar os botões correspondentes na mesma ordem.
3. Se o jogador acertar a sequência, uma nova sequência será mostrada, adicionando um novo passo.
4. O jogo continua até que o jogador erre a sequência, encerrando o jogo.


## 🤝 Contribuições
Contribuições, issues e solicitações de pull requests são bem-vindas! Para mudanças maiores, por favor, abra uma issue primeiro para discutir o que você gostaria de mudar.
