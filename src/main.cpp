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
  Serial.begin(9600); // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  delay(100);				// Optional delay. Some board do need more time after init to be ready
	// Show details of PCD - MFRC522 Card Reader details. 
  // This is helpful to troubleshoot the connection to the RFID reader. If it shows no connection, review the wiring
  mfrc522.PCD_DumpVersionToSerial();	

  //Connects to the Wifi
  start_wifi();

  //Prepares the MQTT connection to the Tago.io server
  setmqtt_server();

  //Button to set the RFID in Record mode and record the cards
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