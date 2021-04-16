#ifndef RFID_FUNCTIONS.h
#define RFID_FUNCTIONS.h

#include <MFRC522.h>

//Pins for the MFRC component and button
#define SS_PIN 9
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

/*********************  Função Novo Cartao     *********************************************
 * 
 * Base para registro de novos cartões
 * aciona a função novo_cartão no main para registro da base quando botão esitver apertado
 * 
 * Principal referência para o endtendimento dos comandos do módulo de RFID 
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


#endif