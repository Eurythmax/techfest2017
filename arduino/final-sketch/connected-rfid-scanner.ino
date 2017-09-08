
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <SPI.h>
#include <MFRC522.h>
#include "MFRC522.h"

// Update these with values suitable for your network.
#define RST_PIN  D3 // RST-PIN for RC522 - RFID - SPI - Modul GPIO5
#define SS_PIN  D8 // SDA-PIN for RC522 - RFID - SPI - Modul GPIO4

const char* ssid = "Stylight Guest";
const char* password = "makestylehappen";
const char* mqtt_server = "technetwork.azure-devices.net";

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

WiFiClientSecure espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);    // Initialize serial communications
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.autoConnect("TECHFESTPROTO");

  client.setServer(mqtt_server, 8883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("esp8266_0BDAD6", "technetwork.azure-devices.net/esp8266_0BDAD6","SharedAccessSignature sr=technetwork.azure-devices.net%2Fdevices%2Fesp8266_0BDAD6&sig=PxQfiGJvtNV5AltkPhlJ%2FJAhkW2q41C67A42R4B6iKs%3D&se=1505213331")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("devices/esp8266_0BDAD6/messages/events/", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}

void loop() {



  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  if (!client.connected()) {
     reconnect();
  }

  unsigned long UID_unsigned;
  UID_unsigned =  mfrc522.uid.uidByte[0] << 24;
  UID_unsigned += mfrc522.uid.uidByte[1] << 16;
  UID_unsigned += mfrc522.uid.uidByte[2] <<  8;
  UID_unsigned += mfrc522.uid.uidByte[3];

  String UID_string =  (String)UID_unsigned;
  //CHANGE ORIGIN by the name of the scanner in the supply chain
  UID_string = "ORIGIN:"+UID_string ;
  char v[20];
  UID_string.toCharArray(v,20);
  client.publish("devices/esp8266_0BDAD6/messages/events/", v);
  Serial.print("Publish message: "+UID_string);

  delay(3000);
 }
