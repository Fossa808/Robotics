#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
char data = 0;

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Welcome");
  display.display();

  delay(3000);
}

void loop() {
  display.clearDisplay();
  if (Serial.available() > 0){
    data = Serial.read();
    Serial.print(data);
    Serial.print("/n");
    if (data == '1'){
      Display();
     display.println("1");
     display.display();
     delay(2000);
    }
    
  }
}
void Display(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}
