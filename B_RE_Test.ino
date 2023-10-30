void setup() {
  // put your setup code here, to run once:
  pinMode(11, INPUT); //Button in
  pinMode(12, INPUT); //Rotary Encoder In
  pinMode(13, OUTPUT); //Button Test
  pinMode(14, OUTPUT); //Rotary Encoder Test
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Button Change output on a high
  if(digitalRead(11) == HIGH)
  {
    digitalWrite(13, HIGH);
  }

  //Button Change output on a low
  if(digitalRead(11) == LOW)
  {
    digitalWrite(13, LOW);
  }

  //Rotarty Encoder change output on a high
  if(digitalRead(12) == HIGH)
  {
    if(digitalRead(14) == HIGH)
    {
      digitalWrite(14, LOW);
    }
    else
    {
      digitalWrite(14, HIGH);
    }
  }
}
