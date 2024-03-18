#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
String UID = "D3 D8 D9 2E";
byte lock = 0;
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);
19
void setup() {
Serial.begin(9600);
servo.write(70);
lcd.init();
lcd.backlight();
servo.attach(3);
SPI.begin();
rfid.PCD_Init();
}
void loop() {
lcd.setCursor(4, 0);
lcd.print("Welcome!"); // Display welcome message on the LCD
lcd.setCursor(1, 1);
lcd.print("Put your card"); // Prompt the user to put their card
if (!rfid.PICC_IsNewCardPresent())
return; // If no new card is present, exit the loop
if (!rfid.PICC_ReadCardSerial())
return; // If card read failed, exit the loop
lcd.clear(); // Clear the LCD screen
lcd.setCursor(0, 0);
lcd.print("Scanning"); // Display scanning message on the LCD
Serial.print("NUID tag is :");
String ID = "";
for (byte i = 0; i < rfid.uid.size; i++) {
20
lcd.print(".");
ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
ID.concat(String(rfid.uid.uidByte[i], HEX));
delay(300);
}
ID.toUpperCase();
if (ID.substring(1) == UID && lock == 0) {
servo.write(70); // Lock the door by moving the servo to position 70
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Door is locked"); // Display door locked message on the LCD delay(1500);
lcd.clear();
lock = 1; // Set lock status to locked
} else if (ID.substring(1) == UID && lock == 1) {
servo.write(200); // Unlock the door by moving the servo to position 200
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Door is open"); // Display door open message on the LCD delay(1500);
lcd.clear();
lock = 0; // Set lock status to unlocked
} else {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Wrong card!"); // Display wrong card message on the LCD delay(1500);
21
lcd.clear();
}
}
