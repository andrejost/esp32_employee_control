#ifndef RFIDFUNCTIONS.h
#define RFIDFUNCTIONS.h

//MFRC522 Library
#include <MFRC522.h>

//MQTT Library to connect to Tago.io using MQTT
#include <PubSubClient.h>

//Reference to the connections files where all connections to Wifi and MQTT will stay
#include "connections.h"

//Pins for the MFRC component and button
#define SS_PIN 9
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String cartoes_registrados[25] = {"" , "", "" , "", "" , "", "" , "", "" , "", "", "" , "", "" , "", "" , "", "" , "", "" , "", "" , "", "", ""};
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
  
  if (cartoes_registrados[1] == "")
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
    
        //Serial.println(content1);
            
        for (int i = 1; i < 14; i++){
          cartoes_registrados[i] = content1[i];
          cartao1.concat(cartoes_registrados[i]);
        }          
                                
        Serial.println("NOVO CARTÃO REGISTRADO NA POSIÇÃO 1: " + cartao1);

      }
      else{
          cartao2 ="";
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
            //Serial.println(content1);
            
            for (int i = 14; i < 26; i++){
              cartoes_registrados[i] = content1[i-13];
              cartao2.concat(cartoes_registrados[i]);
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
  /*************************** Valida Cartão lido agora  - Fim *****************/

  /*************************** Compara cartão com a base atual - Início ********/
  if (cartao_atual.equals(cartao1))
  {
    Serial.println("*********************************************************");
    Serial.println("******** Autorizado - Cartão 1! *************************");
    Serial.println("*********************************************************");
    delay(500);

    publish_mqtt("Cartao 1");

    cartao_atual = "";
  }
  else if (cartao_atual.equals(cartao2))
  {
    Serial.println("*********************************************************");
    Serial.println("******** Autorizado - Cartão 2! *************************");
    Serial.println("*********************************************************");
    delay(500);

    publish_mqtt("Cartao 2");
      
    cartao_atual = "";
  }
  else {
    delay(2000);
    Serial.println("*********************************************************");
    Serial.println("Acesso não autorizado - Por favor entre com cartão válido");
    Serial.println("*********************************************************");
    delay(2000);
    cartao_atual = "";
  }
  /*************************** Compara cartão com a base atual - Fim ************/
      
  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();    

}


#endif