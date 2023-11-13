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
byte BI = 1;
byte BO = 2;
byte CLK = 3;
byte DT = 4;
byte count = 0;

//Game Mechanic variables
bool gameActive = false;
bool firstGame = true;
bool waitingForInput = false;
unsigned long startTime = 0;
int msForInput = 5000;
byte score = 0;
byte reqAction = 0;
float accThreshold = 3;



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
  
  if(!gameActive && firstGame){
    //LCD intro statement
    lcd.setCursor(0,0);
    lcd.print("Football Bop-It");
    lcd.setCursor(1,0);
    lcd.print("Snap it to Start");

    //Look for input
    if(digitalRead(BI) == HIGH){
      gameActive = true;
      firstGame = false;
    }
  }

  //LCD end game 
  if(!gameActive && !firstGame && score < 99){
    lcd.setCursor(0,0);
    lcd.print("Score: " + score);
    lcd.setCursor(1,0);
    lcd.print("Play Again?");
    //Look for input
    if(digitalRead(BI) == HIGH){
      gameActive = true;
      score = 0;
    }
  }

  if(!gameActive && !firstGame && score == 99){
    lcd.setCursor(0,0);
    lcd.print("TOUCHDOWN!");
    lcd.setCursor(1,0);
    lcd.print("Play Again?");
    //Look for input
    if(digitalRead(BI) == HIGH){
      gameActive = true;
      score = 0;
    }
  }

  //Game active
  if(gameActive){

    //Waiting for input and time not up
    if(waitingForInput && ((millis() - startTime) < msForInput)){
      
      //Show action on LCD
      if(reqAction == 1){
        lcd.setCursor(0,0);
        lcd.print("Snap It!");
        lcd.setCursor(1,0);
        lcd.print("Score: " + score);
      }
      else if(reqAction == 2){
        lcd.setCursor(0,0);
        lcd.print("Change the Play!");
        lcd.setCursor(1,0);
        lcd.print("Score: " + score);
      }
      else if(reqAction == 3){
        lcd.setCursor(0,0);
        lcd.print("Throw It!");
        lcd.setCursor(1,0);
        lcd.print("Score: " + score);
      }

      //Look for inputs
      //Snap it
      if(digitalRead(BI) == HIGH){
        //If Required action increment score and continue, else end game
        if(reqAction == 1){
          waitingForInput = false;
          score = score + 1;
        }
        else{
          waitingForInput = false;
          gameActive = false;
        }
      }
      //Throw it
      else if(sqrt(pow(mpu6050.getAccX(),2) + pow(mpu6050.getAccY(),2) + pow(mpu6050.getAccZ(),2)) > accThreshold){
        //If Required action increment score and continue, else end game
        if(reqAction == 2){
          waitingForInput = false;
          score = score + 1;
        }
        else{
          waitingForInput = false;
          gameActive = false;
        }
      }
      else if(currentStateCLK != lastStateCLK  && currentStateCLK == 1){
        
      }
    }
    //Time is up
    else if(waitingForInput && ((millis() - startTime) > msForInput)){
      waitingForInput = false;
      gameActive = false;
    }
    //Action done correctly find new action
    else if(!waitingForInput and score < 99){
      reqAction = random(1, 4);
      waitingForInput = true;
    }
    else if(!waitingForInput and score == 99){
      gameActive = false;
    }
  }

  //Remember last CLK state for Rotary Encoder
	lastStateCLK = currentStateCLK;

  //Put in a slight delay to help debounce the reading for rotary encoder
	delay(10);
}
















