#include <LiquidCrystal.h> //LCD Header File
//4 pin mode LCD (8 pin does not have convenient package and it does same thing just 2x faster
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //This is most common setup of MC pins but can also change pins, represent LCD pins (rs, en, d4, d5, d6, d7)

//Setup the environment
void setup() {
  lcd.begin(16, 2); //Sets up LCD to use 16 columns and 2 rows
  pinMode(X, INPUT) // Push Button Pin Input (Left as "X" so we can pick pins later)
}

void loop() {
  lcd.print("Text") //Writes string to LCD's current line and position
  lcd.setCursor(0, 1); //Sets print statement to appear on 2nd Line
  //lcd.clear() //Clears Display
  //lcd.scrollDisplayRight(); //Scrolls display 
  if(digitalRead(X) == HIGH) //Read pin to do something when a high input is detected
  { 
    lcd.print(millis()) //Prints ms since start
  }
  
}