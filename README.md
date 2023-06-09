Eduardo Fedeli Souza RM:550132
Jéssica Brum Maia Filho RM:97944
Sofia Amorim Coutinho RM:552534
Otávio Vitoriano da Silva RM:552012
Gabriel Torres Luiz RM: 98600

# TerrarI.A.

Este programa permite controlar um sistema de irrigação automática usando um Arduino. O sistema monitora a umidade do solo e ativa uma bomba (simulada por um motor CC) para irrigar o solo quando necessário, exibe temperatura e umidade em display e possui um sistema liga/desliga controlado por sensor infravermelho.

## Funcionalidades

- Monitoramento da umidade do solo e exibição no display LCD.
- Controle da bomba de irrigação através de um relê para ativar/desativar a irrigação.
- Leitura da temperatura ambiente e exibição no display LCD.
- Recebimento de comandos via controle remoto infravermelho para ligar/desligar o sistema.

## Componentes Utilizados

- Arduino Uno
- LED Vermelho
- LED Verde
- LED Azul
- Múltiplos resistores
- Sensor de umidade do solo
- Sensor de temperatura (TMP36)
- Display LCD 16x2
- Potenciômetro 250kΩ
- Sensor infravermelho
- Relé para controle da bomba
- Fonte de energia 5V

## Bibliotecas Utilizadas

- LiquidCrystal.h: Biblioteca para controle do display LCD.
- IRremote.h: Biblioteca para controle do sensor infravermelho.

## Instalação e Configuração

1. Conecte os componentes ao Arduino conforme o esquema de circuito fornecido.
2. Faça o upload do código para o Arduino utilizando a IDE do Arduino.
3. Abra o Monitor Serial para visualizar os dados de umidade, temperatura e códigos infravermelhos recebidos.

## Uso

1. Ligue o sistema pressionando o botão "Power" no controle remoto.
2. O sistema iniciará o monitoramento da umidade do solo e exibirá os valores no display LCD.
3. Se a umidade estiver abaixo do limite, a bomba será ativada para irrigar o solo.
4. A temperatura ambiente também será exibida no display LCD.
5. Para desligar o sistema, pressione novamente o botão "Power" no controle remoto.

## Contribuição

Contribuições são bem-vindas! Se você encontrar algum problema ou tiver sugestões de melhoria, por favor, abra uma issue neste repositório.
