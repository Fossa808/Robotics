int analogPin = A0; 

int val = 0;  

int led = 12;

int ledvalue = 0;  

void setup() 

{

  Serial.begin(9600); 

  pinMode(led,OUTPUT);

}



void loop() 

{

  val = analogRead(analogPin);

  ledvalue = map(val, 0,1023,0,255);

  Serial.println(ledvalue);

  analogWrite(led,ledvalue);        

}
