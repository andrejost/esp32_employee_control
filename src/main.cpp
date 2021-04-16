//Libs for the project
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <PubSubClient.h>

//Custom Includes
#include "credentials.h"
#include "rfid_functions.h"	

int botao = 4, autorizacao = 0;

String cartao_atual ="";
String cartoes_registrados[25] = {"" , "", "" , "", "" , "", "" , "", "" , "", "", "" , "", "" , "", "" , "", "" , "", "" , "", "" , "", "", ""};
String cartao1 = "";
String cartao2 = "";

void novo_cartao();
int compara_cartao();
 
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  // myServo.attach(3);    //servo pin
  // myServo.write(0);     //servo start position
  pinMode(botao, INPUT);
  Serial.println("Por favor colocar o cartão a ser validado");
  Serial.println();
  autorizacao = 0;

}
void loop(){
  
  if(digitalRead(botao) == HIGH){ // caso o botão esteja apertado, entra no modo de registro de novo RFID
      Serial.println("Modo registro de cartão");
      novo_cartao();  
  } 

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
  
  delay(3000);
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
    Serial.println("******** Autorizado - Cartão 1! Seja Bem Vindo!**********");
    Serial.println("*********************************************************");
    delay(500);
    // myServo.write(90);
    // delay(2000);
    // myServo.write(0);
    cartao_atual = "";
  }
  else if (cartao_atual.equals(cartao2))
  {
    Serial.println("*********************************************************");
    Serial.println("******** Autorizado - Cartão 2! Seja Bem Vindo!**********");
    Serial.println("*********************************************************");
    delay(500);
    // myServo.write(90);
    // delay(2000);
    // myServo.write(0);
      
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