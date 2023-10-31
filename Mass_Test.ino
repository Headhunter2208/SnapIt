//Libraries
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Createing Instances
MPU6050 mpu6050(Wire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//RE clock states
int currentStateCLK;
int lastStateCLK;

//Digital Pins for Button and Rotary Encoder
int BI = 1;
int BO = 2;
int CLK = 3;
int DT = 4;
int count = 0;

void setup() {
  //Initialize Accelerometer
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // initialize the LCD, 
  lcd.begin(0x27, 16, 2);
  lcd.backlight();

  //Initialize Button
  pinMode(BI,INPUT);
  pinMode(BO,OUTPUT);

  //Initialize Rotary Encoder
  pinMode(CLK,INPUT); 
	pinMode(DT,INPUT);
  lastStateCLK = digitalRead(CLK);
}

void loop() {
  //Updating mpu and rotary encoder
  mpu6050.update();  
  currentStateCLK = digitalRead(CLK);

  //Button Test
  if(digitalRead(BI) == HIGH){
    digitalWrite(BO) = HIGH
  }
  else{
    digitalWrite(BO) = LOW
  }

  //Rotary Encoder Test
  lcd.setCursor(0,0);
  // If last and current state of CLK are different, then pulse occurred React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    count = count + 1;
    lcd.print(count);
	}

  //Accelerometer Test
  lcd.setCursor(1,0);
  lcd.print(sqrt(pow(mpu6050.getAccX(),2) + pow(mpu6050.getAccY(),2) + pow(mpu6050.getAccZ(),2)));
	
  
  //Remember last CLK state for Rotary Encoder
	lastStateCLK = currentStateCLK;

  //Put in a slight delay to help debounce the reading for rotary encoder
	delay(10);
}