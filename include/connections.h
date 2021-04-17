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

WiFiClient espClient;

PubSubClient client(espClient); //lib required for mqtt

//MQTT Callback Handler
void callback(char* topic, byte* payload, unsigned int length) {
   // handle message arrived
}

// PubSubClient client(MQTT_SERVER, MQTT_PORT, callback, ethClient);

void setmqtt_server(){

  client.setServer(MQTT_SERVER, MQTT_PORT);//connecting to mqtt server

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

void publish_mqtt(String payload){

  //Used to convert the payload to Char  
  char* char_arr;
  char_arr = &payload[0];
  cout << char_arr;

  if (client.connect("esp32rfid", MQTT_USER, MQTT_PASSWORD)){

    Serial.println("Connected to MQTT Server!");
    //This library does not handle the MQTT messages in String format, so it needs to be converted to char
    client.publish("rfid_tag",char_arr);

  };

}

#endif