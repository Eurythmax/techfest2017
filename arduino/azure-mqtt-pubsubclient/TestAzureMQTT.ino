/*
 * Install PubSubClient and WiFiManager libraries
 * Register your IoT devices on Azure IoT Hub
 * Open a SAS token with the iothub-explorer
 *
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>

const char* mqtt_server = "technetwork.azure-devices.net";

WiFiClientSecure espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);    // Initialize serial communications
  WiFiManager wifiManager;
  wifiManager.autoConnect("TECHFEST_NODE_AP");

  client.setServer(mqtt_server, 8883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("**your_registered_device_id**", "**your_iot_hub_name**.azure-devices.net/**your_registered_device_id**","**your_sas_token**")) {
      Serial.println("connected");
    } else {
      Serial.println("can't connect... trying again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {

   if (!client.connected()) {
      reconnect();
   }
   client.publish("devices/esp8266_0BDAD6/messages/events/", "Test message");
    //publish an event every 5 seconds
    delay(5000);
 }
