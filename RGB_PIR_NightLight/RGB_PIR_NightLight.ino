int PIR;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  
  pinMode(13,OUTPUT);
  
  pinMode(9, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  PIR = digitalRead(9);
  if(PIR == 1){
    Serial.println("ON");
    digitalWrite(13,HIGH);
    
    delay(5000);
  }
  else{
    Serial.println("OFF");
    digitalWrite(13,LOW);
  }

}
