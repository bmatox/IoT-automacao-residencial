
## Índice
- Descrição
- Funcionalidades
- Demonstração
- Acesso
- Tecnologias
- Dashboard

## Descrição
Este projeto é um programa para controlar um ventilador com base na temperatura, umidade e movimento do ambiente, usando um sensor DHT11, um sensor PIR e um módulo ESP32. O programa se conecta a uma rede WiFi e a um broker MQTT para enviar e receber mensagens sobre os dados dos sensores e o estado do ventilador. O programa também permite que o usuário ligue ou desligue o ventilador manualmente através de um tópico MQTT. O objetivo deste projeto é criar uma solução inteligente e prática para o controle de ventilação de um ambiente. O público-alvo deste projeto são pessoas que desejam automatizar ou personalizar o funcionamento de um ventilador em sua casa ou escritório. Esse projeto consiste na atividade final da disciplina de Sistemas Ciberfísicos Colaborativos do curso de Ciência da Computação da UNIFOR.

## Funcionalidades
- Leitura da temperatura e umidade do ambiente a cada 2 segundos usando o sensor DHT11;
- Leitura do movimento do ambiente usando o sensor PIR;
- Envio dos dados dos sensores para o broker MQTT nos tópicos `unifor/cps/temp`, `unifor/cps/umid` e `unifor/cps/pir`;
- Recebimento de comandos para ligar ou desligar o ventilador pelo broker MQTT no tópico `unifor/cps/vent`;
- Acionamento do ventilador de acordo com a lógica: se a temperatura for maior que 25°C, a umidade for menor que 80% e houver movimento no ambiente, o ventilador é ligado; caso contrário, o ventilador é desligado;
- Modo manual para ligar ou desligar o ventilador independentemente da lógica, ativado pelo comando `on` ou `off` no tópico `unifor/cps/vent`;
- Envio do estado do ventilador para o broker MQTT no tópico `unifor/cps/vent`, sendo `on` para ligado e `off` para desligado.

## Demonstração
Veja  um vídeo demonstrando o funcionamento do projeto: https://youtu.be/Aegw4ITioyo

## Acesso
Para acessar o projeto, você precisa ter os seguintes componentes:

- Um módulo ESP32;
- Um sensor DHT11;
- Um sensor PIR;
- Um ventilador ou um LED para simular o ventilador;
- Um protoboard e alguns jumpers para fazer as conexões;
- Módulo relé de 5v (J3Y);
- Fonte de alimentação 12v AC/DC;
- Um computador com Arduino IDE instalado e configurado para o ESP32;
- Uma conta no GitHub para clonar o repositório do projeto;
- Uma conta no HiveMQ para usar o broker MQTT.

Siga os seguintes passos para acessar o projeto:

- Clone o repositório do projeto no seu computador usando o comando `git clone https://github.com/bmatox/controle-ventilador-esp32-IoT.git`;
- Abra o arquivo `sketch_nov17a.ino` na Arduino IDE;
- Altere as variáveis `ssid`, `password`, `mqttServer`, `mqttUser` e `mqttPassword` de acordo com os seus dados de rede WiFi e broker MQTT;
- Conecte o ESP32 ao seu computador pela porta USB e selecione a placa e a porta corretas na Arduino IDE;
- Faça o upload do código para o ESP32 e abra o monitor serial para ver as mensagens;
- Conecte os sensores e o ventilador a ESP32 de acordo com o esquema abaixo:
![Imagem do WhatsApp de 2023-12-14 à(s) 01 40 45_a061e772](https://github.com/bmatox/controle-ventilador-esp32-IoT/assets/146227721/8b85c694-d625-449f-a93f-8036ecdc5340)
- Use um cliente MQTT, como o MQTTBox, para se conectar ao broker MQTT e enviar e receber mensagens nos tópicos `unifor/cps/vent`, `unifor/cps/temp`, `unifor/cps/umid` e `unifor/cps/pir`;
- Teste o funcionamento do projeto alterando as condições do ambiente e enviando comandos pelo MQTT.

## Tecnologias
As tecnologias utilizadas neste projeto são:

- C++: linguagem de programação usada para escrever o código do ESP32;
- Arduino IDE: ambiente de desenvolvimento integrado para programar o ESP32;
- ESP32: microcontrolador com WiFi integrado usado para controlar os sensores e o ventilador;
- DHT11: sensor de temperatura e umidade usado para medir as condições do ambiente;
- PIR: sensor de movimento usado para detectar a presença de pessoas no ambiente;
- MQTT: protocolo de comunicação usado para enviar e receber mensagens entre o ESP32 e o broker;
- HiveMQ: broker MQTT usado para intermediar a comunicação entre o ESP32 e o cliente MQTT;
- MQTTBox: cliente MQTT usado para testar o projeto e enviar comandos para o ventilador.

## Dashboard

  Dashboard:
Para visualizar e interagir com os dados dos sensores e o estado do ventilador, você pode usar o dashboard do node-red. O dashboard do node-red é um módulo que fornece um conjunto de nós para criar uma interface gráfica para o seu projeto. Você pode personalizar o layout, o tema, os widgets e as configurações do dashboard, e acessá-lo pelo editor do node-red ou pela aba dashboard na barra lateral. A interface do dashboard está disponível em http://localhost:1880/ui (se as configurações padrão forem usadas).

No dashboard do node-red, você pode:

- Acompanhar a evolução da temperatura e umidade por meio de um gráfico, usando o nó chart;
- Ligar e desligar o ventilador por meio de um nó switch (on/off), usando o nó ui-switch;
- Ver indicadores visuais que mostram quando o ventilador/sensor estão ligados, usando os nós ui-led e ui-text.

Para usar o dashboard do node-red, você precisa:

- Instalar o módulo node-red-dashboard, usando o menu - manage palette ou o comando npm i node-red-dashboard no seu diretório de usuário do node-red - tipicamente ~/.node-red;
- Reiniciar a sua instância do node-red e verificar se os nós UI estão disponíveis na paleta e se a aba dashboard está presente no painel direito;
- Arrastar e soltar os nós UI que você deseja usar no seu fluxo e configurá-los de acordo com os seus dados e preferências;
- Conectar os nós UI aos nós MQTT que recebem e enviam as mensagens para o broker;
- Clicar em deploy e acessar o dashboard pelo editor do node-red ou pela aba dashboard na barra lateral;
- Passo a passo mais detalhado da instalação: https://nodered.org/docs/getting-started/windows

Agradeço a todos que contribuíram de alguma forma para o sucesso desse projeto.

