#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9//defining reset pin
#define SS_PIN 10//defining slave select
byte readCard[4];
byte a = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);// Initialize LCD object with I2C address 0x27
MFRC522 mfrc522(SS_PIN, RST_PIN); // Initialize MFRC522 RFID reader object
void setup() {
Serial.begin(9600); // Initialize serial communication at baud rate 9600
17
lcd.init();// Initialize the LCD
lcd.backlight();// Turn on the backlight
while (!Serial); // Wait for the serial connection to be established
SPI.begin(); // Initialize SPI bus
mfrc522.PCD_Init();// Initialize the MFRC522 RFID reader
delay(4);// Delay for 4 milliseconds
mfrc522.PCD_DumpVersionToSerial(); // Print MFRC522 version information to the serial
lcd.setCursor(2, 0);
lcd.print("Put your card"); // Display message on the LCD
}
void loop() {
if ( ! mfrc522.PICC_IsNewCardPresent()) {
return 0; // If no new card is present, exit the loop
}
if ( ! mfrc522.PICC_ReadCardSerial()) {
return 0; // If card read failed, exit the loop
}
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Scanned UID");
a = 0;
Serial.println(F("Scanned PICC's UID:"));
for ( uint8_t i = 0; i < 4; i++) { //
readCard[i] = mfrc522.uid.uidByte[i];
18
Serial.print(readCard[i], HEX);
Serial.print(" ");
lcd.setCursor(a, 1);
lcd.print(readCard[i], HEX);
lcd.print(" ");
delay(500);
a += 3;
}
Serial.println("");
mfrc522.PICC_HaltA();
return 1;
}
