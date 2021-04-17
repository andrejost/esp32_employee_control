//Libs for the project
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

//Custom Includes
#include "rfidfunctions.h"
#include "connections.h"	

int botao = 4;
 
void setup() 
{
  Serial.begin(115200); // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  //Connects to the Wifi
  start_wifi();

  //Prepares the MQTT connection to the Tago.io server
  setmqtt_server();

  pinMode(botao, INPUT);
  Serial.println("Por favor colocar o cartão a ser validado");
  Serial.println();

}

void loop(){
  
  if(digitalRead(botao) == HIGH){ // caso o botão esteja apertado, entra no modo de registro de novo RFID
      Serial.println("Modo registro de cartão");
      novo_cartao();  
  } 

  //Shows the current registered card database  
  base_cartao();
  
  delay(3000);

  //Checks whether a card is valid
  valida_cartao();
  
} 