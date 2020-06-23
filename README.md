# GSM-Weather-Station
Estação meteorológica que mede microclimas e envia esses dados via GSM. 
## Resumo: 
Este projeto propõe uma rede de monitoramento climático utilizando estações meteorológicas autonomas, que transmitem os dados coletados atraves rede GSM (Global System for Mobile Communications), para um Middleware IoT, responsável por fazer a persistencia dos dados e fornecer informações sobre o clima para as diversas aplicações, focadas em ajudar os usuários no planejamento da rotina diária.
## Programas Necessários:
-**IDE arduino**, https://www.arduino.cc/en/Main/Software.

-**Cura Software** ou **Slic3r**.

## Companentes necessários:
- 1 Módulo A6 Gsm/Gprs.

- 1 Arduino mega.

- 1 Módulo sensor de chuva.

- 1 Módulo sensor de luminosidade de luz LDR.

- 1 Sensor de umidade e temperatura DHT 11.

- 1 Atiny 85.

- 1 Regulador de Tensão 7805 5V.

- 1 Relé nec 5V.

- 1 Módulo carregador tp4056.

- 3 Painel Placa Solar 12v 1.50w Carregador Ecologico 9v.

- 1 Modulo Conversor Tensão Dc/dc Step Up.

## Arquitetura da solução proposta:
<img src=https://github.com/matheussantosmonteiro12/GSM-Weather-Station/blob/master/Fotos/devices_esta%C3%A7%C3%A3o.png>


## Circuito de alimentação:
<img src= https://github.com/matheussantosmonteiro12/GSM-Weather-Station/blob/master/Fotos/circuito_de_alimentacao..png>

**1) Relé, 2) Microcontrolador, 3) Carregador de bateria, 4) Regulador de tensão.**


## Circuito principal:
<img src= https://github.com/matheussantosmonteiro12/GSM-Weather-Station/blob/master/Fotos/iotDivece.png >

**1) Sensor de gás, 2) Sensor de temperatura e umidade, 3) Sensor de luminosidade, 4) Sensor de chuva, 5) A6 GSM/GPRS, 6) Microcontrolador.**


## Versão final da estação:
<img src= https://github.com/matheussantosmonteiro12/GSM-Weather-Station/blob/master/Fotos/esta1.jpg >

#### Link do Artigo sobre esse projeto:
https://ieeexplore.ieee.org/abstract/document/8896242

#### OBS:
Para qualquer outras duvidas me mande um email no matheus.monteiro@uiot.org. 




