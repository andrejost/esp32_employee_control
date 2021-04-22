#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// WiFi configuration
#define WIFI_SSID "INSERT NETWORK SSID HERE"
#define WIFI_PW "INSERT PASSWORD FOR YOUR WIFI NETWORK HERE"

//Tago.io MQTT Server. 
const char* MQTT_SERVER = "mqtt.tago.io"; 
//1883 for non secure connection and 8883 for secure connection using SSL. Change 0000 for the MQTT port 1883 or 8883
//I tried using 8883 as the MQTT port but I think that on the free plans, they only allow using port 1883
const int MQTT_PORT = 0000; 
//Tago.io Device Token
#define MQTT_USERNAME "INSERT TAGO.IO DEVICE TOKEN CREATED HERE" 
//Tago.io Device User
#define MQTT_USER "INSERT TAGO.IO DEVICE NAME CREATE HERE"
//Tago.io Default Topic to add data
#define MQTT_TOPIC "tago/data/post"

#endif