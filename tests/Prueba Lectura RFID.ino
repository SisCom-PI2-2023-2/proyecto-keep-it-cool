#include <SPI.h>
#include <MFRC522.h>   //GithubCommunity Version 1.4.10

#define RST_PIN  0    //Pin 9 para el reset del RC522
#define SS_PIN  15   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

char uidTarjeta[16];

void setup() {
  Serial.begin(9600); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Lectura del UID");
}

void loop() {

  // Limpiar uidTarjeta
  for (int i = 0; i < 16; i++) {
    uidTarjeta[i] = 0;
  }
  
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) {    
    Serial.println("Lectura del UID");

    //Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial()) {

        // Convertir array de bytes que representan el codigo hexadecimal a string.
        sprintf(uidTarjeta, "%02x%02x%02x%02x", mfrc522.uid.uidByte[0], mfrc522.uid.uidByte[1], mfrc522.uid.uidByte[2], mfrc522.uid.uidByte[3]);
        Serial.print("Se leyo una tarjeta con codigo:");
        Serial.println(uidTarjeta);

        // Terminamos la lectura de la tarjeta  actual
        mfrc522.PICC_HaltA();    
    }      
  } 
}
