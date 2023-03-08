#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

 
#define DHTPIN D3         //DHT11 is connected to GPIO Pin D3

#define trigpin D7
#define echopin D6

String apiKey = "HNJNZN9WLB32M9AF";     //  Enter your Write API key from ThingSpeak
const char* ssid =  "AndroidAP0698";     // Enter your WiFi Network's SSID
const char* pass =  "pjya8081"; // Enter your WiFi Network's Password
const char* server = "api.thingspeak.com";

int dis;
int durat;


float humi;
float temp;
 
DHT dht(DHTPIN, DHT11);
WiFiClient client;
 
void setup() 
{
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);
  
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 

 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(100);
            Serial.print("*");
     }
      Serial.println("");
      Serial.println("WiFi connected");

      display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Welcome");
  
 display.display();

  delay(5000);
}
 
void loop() 
{
  
      humi = dht.readHumidity();
      temp = dht.readTemperature();

digitalWrite(trigpin,LOW);
delay(2);
digitalWrite(trigpin,HIGH);
delay(10);
digitalWrite(trigpin,LOW);

durat=pulseIn(echopin,HIGH); 

dis = durat * 0.0342/2;

Serial.print("Distance=");

 Serial.println(dis);
    
      if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
      {  
       String sendData = apiKey+"&field1="+String(temp)+"&field2="+String(humi)+"&field3="+String(dis)+"\r\n\r\n"; 
       
       //Serial.println(sendData);

       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(sendData.length());
       client.print("\n\n");
       client.print(sendData);

       Serial.print("Temperature: ");
       Serial.print(temp);
       Serial.print("deg C. Humidity: ");
       Serial.print(humi);
       Serial.print("Distance ");
       Serial.print(dis); // 0 means no motion 1 means motion detected 
       Serial.println("%. Connecting to Thingspeak.");
       }
      
      client.stop();

      Serial.println("Sending....");
  
 delay(1000);

 display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Distance:");
  display.print(dis);
  display.println(" cm");
  display.println("Temperature:");
  display.print(temp);
  display.println(" deg. C");
  display.println("Humidity:");
  display.print(humi);
  display.println(" %");

  display.display();
  delay(5000);
 
}
