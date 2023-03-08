#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN D5    
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

String apiWritekey = "ASLTZFG7WOC782AQ"; 
const char* ssid = "AndroidAP0698";
const char* password = "pjya8081" ;
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {

   Serial.println(F("DHTxx test!")); 
   dht.begin();
  
  Serial.begin(115200);
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

 float h = dht.readHumidity();
 
  float t = dht.readTemperature();
  
  float f = dht.readTemperature(true);

 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

 
  float hif = dht.computeHeatIndex(f, h);
 
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  

float temp = t;
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

    Serial.print("Temperature  ");
    Serial.print(temp);
    Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();

  Serial.println("Waiting to upload next reading...");
  Serial.println();
  delay(10000);
}
