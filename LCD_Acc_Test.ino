//Libraries
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Createing Instances
MPU6050 mpu6050(Wire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  //Initialize Accelerometer
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // initialize the LCD, 
  lcd.begin(0x27, 16, 2);
  lcd.backlight();
}

void loop() {
  //Updating mpu and rotary encoder
  mpu6050.update();

  //Accelerometer and LCD Test
  lcd.setCursor(0,0);
  lcd.print(sqrt(pow(mpu6050.getAccX(),2) + pow(mpu6050.getAccY(),2) + pow(mpu6050.getAccZ(),2))); 
}
