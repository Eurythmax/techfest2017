/*Use this sketch to verify that you have a working installation of the NodeMCU + MFRC522

* ---------------------------------------
*             MFRC522      Arduino
*             Reader/PCD   Uno/101
* Signal      Pin          Pin
* ---------------------------------------
* RST/Reset   RST          D3
* SPI SS      SDA(SS)      D8
* SPI MOSI    MOSI         D7
* SPI MISO    MISO         D6
* SPI SCK     SCK          D5
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         D3
#define SS_PIN          D8

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
}

void loop() {
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	 dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
   delay(2000);
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
