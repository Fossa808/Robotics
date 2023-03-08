void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = digitalRead(11); // READING THE PUSHBUTTON
  if (i == 1){
    digitalWrite(8,HIGH);
  }
  else{ 
    digitalWrite(8,LOW);
  }
}
