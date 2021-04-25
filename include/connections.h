#ifndef CONNECTIONS.h
#define CONNECTIONS.h

//Used for converting String to Char when passing the MQTT Payload in topic
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

//Wifi Library for ESP32
#include <WiFi.h>

//MQTT Library for connection to Tago.io using MQTT
#include <PubSubClient.h>

//Library for creating a WebServer object so it can be used for the MQTT stack.
#include <WebServer.h>

//Include file for credentials. In this case, replace credentials.h for credentials_example.h
#include "credentials.h"

//Library used to work with JSON objects when sending to the Tago.io API. 
//To identify the variables and values in you device, Tago.io used a JSON Object
#include <ArduinoJson.h>

//Necessary to work with the ArduinoJSON Library
//The size of the buffer is limited to 256 as this is the limit of the PubSubClient Library
StaticJsonDocument<256> MQTTOBJECT;

//Creates an object to send data using MQTT
WiFiClient espClient;

//lib required for mqtt
PubSubClient client(espClient); 

//MQTT Callback Handler. Not used in this example, but can be used to handle incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
   // handle message arrived
}

// PubSubClient client(MQTT_SERVER, MQTT_PORT, callback, ethClient);

void setmqtt_server(){

  client.setServer(MQTT_SERVER, MQTT_PORT);

  client.setCallback(callback);

}

void start_wifi(){

  //WIFI CONNECTION DATA  
  WiFi.begin(WIFI_SSID,WIFI_PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  
  //WI-FI Startup
  Serial.println("..............");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("..............");

}

void publish_mqtt(String rfid_tag){

  //You need to create a variable to concatenate the Data and format the JSON Object
  char message[256];
  
  //Variables for the RFID TAG and Card Name
  MQTTOBJECT["variable"] = "rfid_tag";
  MQTTOBJECT["value"] = rfid_tag;
  serializeJson(MQTTOBJECT, message);  
          
  if (client.connect("12345", MQTT_USER, MQTT_PASSWORD)){

    Serial.println("Connected to MQTT Server!");

    if(client.publish(MQTT_TOPIC, message)){
      Serial.println("MQTT Data sent successfully !");
    };

  };

}

#endif