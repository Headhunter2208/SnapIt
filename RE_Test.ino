//RE clock statres  
int currentStateCLK;
int lastStateCLK;

//Digital Pins for Rotary Encoder
int O = 2;
int CLK = 3;
int DT = 4;
int count = 0;

void setup() {
  //LED Output
  pinMode(O, OUTPUT);
  
  //Initialize Rotary Encoder
  pinMode(CLK,INPUT); 
	pinMode(DT,INPUT);
  lastStateCLK = digitalRead(CLK);
}

void loop() {
  //Rotary Encoder Test
  // If last and current state of CLK are different, then pulse occurred React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    count = count + 1;
    if(count%2 == 0){
      digitalWrite(O,HIGH);
    }
    else{
      digitalWrite(O,LOW);
    }
	}

  //Remember last CLK state for Rotary Encoder
	lastStateCLK = currentStateCLK;

  //Put in a slight delay to help debounce the reading for rotary encoder
	delay(10);
}
