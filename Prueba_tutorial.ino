#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
void setup() {
Serial.begin(9600); //Iniciamos la comunicación  serial
SPI.begin();        //Iniciamos el Bus SPI
mfrc522.PCD_Init(); // Iniciamos  el MFRC522
Serial.println("Lectura del UID");
}
void loop() {
// Revisamos si hay nuevas tarjetas  presentes
if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
    //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                  } 
                  Serial.println();
                  // Terminamos la lectura de la tarjeta  actual

                    // Write data ***********************************************
                for (int i=0; i < 4; i++) {
                  //data is writen in blocks of 4 bytes (4 bytes per page)
                  status = (MFRC522::StatusCode) mfrc522.MIFARE_Ultralight_Write(pageAddr+i, &buffer[i*4], 4);
                  if (status != MFRC522::STATUS_OK) {
                    Serial.print(F("MIFARE_Read() failed: "));
                    Serial.println(mfrc522.GetStatusCodeName(status));
                    return;
                  }
                }
                Serial.println(F("MIFARE_Ultralight_Write() OK "));
                Serial.println();
                  mfrc522.PICC_HaltA();         
            }      
} 
}