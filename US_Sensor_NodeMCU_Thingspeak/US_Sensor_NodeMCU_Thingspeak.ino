#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

String apiWritekey = "HNJNZN9WLB32M9AF"; 
const char* ssid = "AndroidAP0698";
const char* password = "pjya8081" ;

#define trigpin D7
#define echopin D6

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C


const char* server = "api.thingspeak.com";

WiFiClient client;
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);


int dis;
int durat;

void setup() {
display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Welcome");
  display.display();

  delay(5000);

  
  Serial.begin(115200);

pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}

void loop() {
 display.clearDisplay();
digitalWrite(trigpin,LOW);
delay(2);
digitalWrite(trigpin,HIGH);
delay(10);
digitalWrite(trigpin,LOW);

durat=pulseIn(echopin,HIGH); 

dis = durat * 0.0342/2;

Serial.print("Distance=");

 Serial.println(dis);
 
  

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Distance");
  display.println(dis);

  display.display();
  delay(3000);
  
  float temp = dis;
  
  if (client.connect(server,80)) {
    String tsData = apiWritekey;
    tsData +="&field1=";
    tsData += String(temp);
    tsData += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);

    Serial.print("Distance");
    Serial.print(temp);
    Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();

  Serial.println("Waiting to upload next reading...");
  Serial.println();
  delay(10000);
}
