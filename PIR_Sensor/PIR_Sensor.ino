void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 pinMode(9,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int i = digitalRead(9);
 if (i == 1){
  Serial.println("on");
 }
 else{
  Serial.println("off");
 }
}
