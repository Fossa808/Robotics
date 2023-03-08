int bulb = 2;
char data = 0;
void setup() {
  Serial.begin(9600);
  pinMode(bulb,OUTPUT);
}

void loop() {
  if (Serial.available() > 0){
    data = Serial.read();

    if (data == '1'){
      digitalWrite(bulb,HIGH);
      Serial.println("Bulb ON");
    }
    if (data == '0'){
      digitalWrite(bulb,LOW);
      Serial.println("Bulb OFF");
    }
  }
}
