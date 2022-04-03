void setup()
{
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop()
{
  Red();
  Yellow();
  Green();
}
void Red()
{
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  delay(1000);
}
void Yellow()
{
  digitalWrite(10,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(11,LOW);
  delay(1750);
}
void Green()
{
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  delay(3000);
}
