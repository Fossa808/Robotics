// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "AndroidAP0698";
const char* password = "pjya8081";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output2State = "off";
String output14State = "off";
// Assign output variables to GPIO pins
const int output5 = D5;
const int output4 = D6;
const int output2 = D7;
const int output14 = D1;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output14, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite (output2 , LOW);
  digitalWrite (output14,LOW);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) 
            {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } 
            else if (header.indexOf("GET /5/off") >= 0)
             {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } 
            else if (header.indexOf("GET /4/on") >= 0)
            {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } 
            else if (header.indexOf("GET /4/off") >= 0)
            {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
             else if (header.indexOf("GET /2/on") >= 0)
            {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } 
            else if (header.indexOf("GET /2/off") >= 0)
            {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
             else if (header.indexOf("GET /14/on") >= 0)
            {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, HIGH);
            } 
            else if (header.indexOf("GET /14/off") >= 0)
            {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body{background-color: #000000;} html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button{ box-shadow: 1px px 1px #757272 ; border-radius: 25px; background-color: #FFFCFC; border: none; color: black; padding: 16px 40px;}");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 { box-shadow: 1px 1px 1px #757272  ; background-color:#757272  ;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1><p style= color:white font-size: '60px' > Rancho_Labs  </p></h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p style= color:white > Tubelight ~ " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p style= color:white ><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p style= color:white ><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p style= color:white> Fan 1 ~ " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p style= color:white><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p style= color:white><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
             // Display current state, and ON/OFF buttons for GPIO 2 
            client.println("<p style= color:white > Fan 2 ~ " + output2State + "</p>");
            // If the output2State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p style= color:white ><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p style= color:white><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
             // Display current state, and ON/OFF buttons for GPIO 14  
            client.println("<p style= color:white > Extra ~ " + output14State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output14State=="off") {
              client.println("<p style= color:white ><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p style= color:white ><a href=\"/14/off\"><button class=\"button button14\">OFF</button></a></p>");
            } 
               
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
