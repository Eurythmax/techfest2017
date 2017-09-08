# techfest2017

This is a project to demonstrate how to create a very simple supply chain management tracking system on the blockchain. 
The slidedeck accompanying this workshop can be found here: https://www.slideshare.net/romefort1/supply-chain-management-on-the-blockchain-with-iot-azure-bigchaindb-vuejs

## Project structure

> arduino/

In the arduino directory you'll find a few sketches to run the demo on a NodeMCU and MFRC522

* azure-mqtt-pubsubclient: Contains a sketch to verify your wifi connectivity and connect to to Azure.

* nodemcu-mfrc522: Contains a sketch to verify that your MFRC522 board works properly

* final-sketch: Contains the final sketch for this project, which includes connecting to Azure and sending MQTT message upon tag scanning

> server/

* mqtt-bigchaindb.js : listens to Azure events and either do a CREATE or TRANSFER transaction depending on which scanner the tag has been scanned.

simply run with

``` $ node mqtt-bigchaindb.js ```


* webserver: simple express app that listens to IPDB events and send websockets events to the UI in return

``` $ bin/www ```


> userinterface: simple UI built on Vue.JS which listens to websockets events and update interface with incoming transactions

``` $ npn run dev ```


## Hardware

You'll need a NodeMCU

![alt text](https://statics3.seeedstudio.com/seeed/img/2017-03/QluwTVU7FQIvaC8dZy6x2JaM.jpg "NodeMCU")


and a MFRC522 RFID Scanner

![alt text](http://sklep.celiko.net.pl/images/czujniki/rc522%20schemat.jpg "MFRC522")


* Start with the NodeMCU unplugged

* Download [NodeMCU Driver](https://www.dropbox.com/sh/nqh9yqm9pd9hgg6/AAD0_wmnLMD3OxDO3TCsj4PLa?dl=0) CH341SER_*yourOS* and install it

* Connect the NodeMCU board to the USB port
> ls /dev/tty* should show something like /dev/tty.wchusbserial1420


* If you want to play around with LUA, download [ESPlorer](http://esp8266.ru/esplorer/)

* Download [Arduino IDE](https://www.arduino.cc/en/Main/Software)

* Configure your Arduino IDE to support ESP8266

Do run the project, you'll need to flash your arduino with arduino/final-sketch/connected-rfid-scanner.installation
