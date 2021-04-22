#ifndef RFIDFUNCTIONS.h
#define RFIDFUNCTIONS.h

#include <string>

//MFRC522 Library
//#include <MFRC522.h>

//MQTT Library to connect to Tago.io using MQTT
// #include <PubSubClient.h>

//Reference to the connections files where all connections to Wifi and MQTT will stay
#include "connections.h"

//Pins for the MFRC component and button
//Pin 21 used in SS_PIN is the SDA Pin
#define SS_PIN 21
//Pin 22 used in RST_PIN is the Reset Pin
#define RST_PIN 22
// Create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN);   

String cartao1 = "";
String cartao2 = "";
String cartao_atual ="";

/*********************  Função Novo Cartao     *********************************************
 * 
 * Base para registro de novos cartões
 * aciona a função novo_cartão no main para registro da base quando botão esitver apertado
 * 
 * Principal referência para o entendimento dos comandos do módulo de RFID 
 * https://forum.arduino.cc/index.php?topic=263865.0
 * 
 *****************************************************************************************/
void novo_cartao(){
  
  String content1;
  
  Serial.println("MODO REGISTRO");
  
  if (cartao1[1] == '\0') //Checks whether there is a card already registered in the array
  {
        
    // Look for new cards
      if ( ! mfrc522.PICC_IsNewCardPresent()) 
      {          
        return;
      }
    // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) 
      {
        return;
      }
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
        //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        //Serial.print(mfrc522.uid.uidByte[i], HEX);
        content1.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content1.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
    
      Serial.println(content1);
            
      for (int i = 1; i < 12; i++)
      {
        // cartoes_registrados[i] = content1[i];
        cartao1.concat(content1[i]);
      }          

    Serial.println("NOVO CARTÃO REGISTRADO NA POSIÇÃO 1: " + cartao1);
  
  }
  else if (cartao2[1] == '\0') //Checks whether there is a card already registered in the array
  {
          
          // Look for new cards
          if ( ! mfrc522.PICC_IsNewCardPresent()) 
          {
            return;
          }
          // Select one of the cards
          if ( ! mfrc522.PICC_ReadCardSerial()) 
          {
            return;
          }

          for (byte i = 0; i < mfrc522.uid.size; i++) 
          {
            //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            //Serial.print(mfrc522.uid.uidByte[i], HEX);
            content1.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content1.concat(String(mfrc522.uid.uidByte[i], HEX));
        
          }
            
            Serial.println(content1);
            
          for (int i = 1; i < 12; i++)
          {
            cartao2.concat(content1[i]);
          }          
     
          Serial.println("NOVO CARTÃO REGISTRADO NA POSIÇÃO 2: " + cartao2);
                        
  }
        
}

  
void base_cartao(){  

  Serial.println();  
  Serial.println("-------- Base de Cartões Início --------------------");
  Serial.println();
  Serial.println("Cartão 1:");
  Serial.println(cartao1);
  Serial.println();
  Serial.println("Cartão 2:");
  Serial.println(cartao2);
  Serial.println();
  Serial.println("-------- Base de Cartões Fim --------------------");
  Serial.println();

}

void valida_cartao() {

  /*************************** Valida Cartão lido agora  - Início **************/
  String content2 ="";
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
    // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);
  mfrc522.PICC_WakeupA(bufferATQA, &bufferSize);

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    content2.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content2.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
    
  for (int i = 1; i < 12; i++){
    cartao_atual.concat(content2[i]);
  }          
  
  /*************************** Compara cartão com a base atual - Início ********/
  if (cartao_atual.equals(cartao1) | cartao_atual.equals(cartao2))
  {
    Serial.println("*********************************************************");
    Serial.println("******** Autorizado *************************************");
    Serial.println("*********************************************************");
    Serial.println("** Cartão Inserido: " + cartao_atual + " *************************");
    Serial.println("*********************************************************");
    
    delay(500);

    publish_mqtt(cartao_atual);
    
    cartao_atual = "";
  }
  else {
    delay(100);
    Serial.println("*********************************************************");
    Serial.println("Acesso não autorizado - Por favor entre com cartão válido");
    Serial.println("*********************************************************");


    cartao_atual = "";
  }
        
  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();    

}


#endif