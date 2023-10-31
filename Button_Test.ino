//Digital Pins for Button
int BI = 1;
int BO = 2;

void setup() {
  // put your setup code here, to run once:
  //Initialize Button
  pinMode(BI,INPUT);
  pinMode(BO,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Button Test
  if(digitalRead(BI) == HIGH){
    digitalWrite(BO, HIGH);
  }
  else{
    digitalWrite(BO, LOW);
  }
}
