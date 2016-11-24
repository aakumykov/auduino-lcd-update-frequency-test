#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

unsigned long readInterval = 100;
unsigned long displayInterval = readInterval * 2;

unsigned long lastRead = 0;
unsigned long lastDisplay = 0;
String inputData = "";
LiquidCrystal_PCF8574 lcd(0x27);

String readInputData(){
  int incomingBytes = Serial.available();
  String data = "";
  if (incomingBytes > 0) {
    for (int i=0; i<incomingBytes; i++){
      data += String( char(Serial.read()) );
    }
  } else {
    data = "*no*";
  }
  return data;
}


void setup() {
    lcd.begin(16,2);
    lcd.setBacklight(255);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("*two delays loop");
    
    lcd.setCursor(0,1);
    lcd.print(String(readInterval)+"ms-"+String(displayInterval)+" ms");
    
    delay(1000);
    Serial.begin(9600);
}
 
void loop() {
  unsigned long currentRead = millis();
  if ((currentRead - lastRead) > readInterval) {
      lastRead = currentRead;
      lcd.setCursor(0,0); lcd.print("                ");
      lcd.setCursor(0,0); lcd.print("r("+String(readInterval)+"):"+String(currentRead));
  }

  unsigned long currentDisplay = millis();
  if ((currentDisplay - lastDisplay) > displayInterval) {
    lastDisplay = currentDisplay;
    lcd.setCursor(0,1); lcd.print("                ");
    lcd.setCursor(0,1); lcd.print("d("+String(displayInterval)+"):"+String(currentDisplay));
  }
}
