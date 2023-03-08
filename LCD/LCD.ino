#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin();
  lcd.backlight();
}

void loop()
{
  lcd.clear();
  lcd.print("Rancho Labs");
  lcd.setCursor (0,1); 
  lcd.print("Hello World!");
  delay(2000);
}
