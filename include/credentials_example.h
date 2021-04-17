#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// WiFi configuration
#define WIFI_SSID "INSERT NETWORK SSID HERE"
#define WIFI_PW "INSERT PASSWORD FOR YOUR WIFI NETWORK HERE"

//Tago.io MQTT data

//Tago.io MQTT data
const char* MQTT_SERVER = "mqtt.tago.io"; //Tago.io MQTT Server. If you are using other MQTT servers, replace them here.
const uint16_t MQTT_PORT = 0000; //1883 for non secure connection and 8883 for secure connection using SSL. Change 0000 for the MQTT port 1883 or 8883
//Tago.io Device Token
#define MQTT_USERNAME "INSERT TAGO.IO DEVICE TOKEN CREATED HERE" 
//Tago.io Device User
#define MQTT_USER "INSERT TAGO.IO DEVICE NAME CREATE HERE"

#endif