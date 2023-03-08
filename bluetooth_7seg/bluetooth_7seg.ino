char data = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i= 6;i<=12;i++)
   {
    pinMode(i,OUTPUT);
   }
}
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    data = Serial.read();
    Serial.print(data);
    Serial.print("/n");
  
    if (data == '1'){
      digitalWrite(10,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(12,LOW);
        digitalWrite(9,LOW);
        digitalWrite(11,LOW);
        digitalWrite(8,HIGH);
    }
     
    
    else if (data == '2')
    digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(8,LOW);
    
  }
  else if(data == '3'){
    digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(8,HIGH);
  }
}
