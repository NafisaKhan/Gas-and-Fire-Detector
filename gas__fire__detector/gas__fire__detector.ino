//libraries for LCD and Servo
#include <LiquidCrystal.h>
#include <Servo.h>

//LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);
LiquidCrystal lcd(13 , 12 , 11 ,10 ,9 ,8);

//initilizing servo and its position
Servo myServo; 
int pos = 0;

//initilizing pins
int GasPin = 2;
int FirePin = 3;
int buzzer = 4;
int ledRed = 7;
int ledGreen = 6;

void setup()
{
  //input pins
  pinMode(GasPin, INPUT);
  pinMode(FirePin, INPUT);
  //output pins
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //servo pin
  myServo.attach(5);
}

void loop() 
{
   //Only Gas detection
  if((digitalRead(GasPin) == HIGH) && (digitalRead(FirePin) == LOW))
  { 
    //LCD Display for gas
    lcd.setCursor(0,0);
    lcd.print("Gas Detacted!!!");
    //Red light ON
    digitalWrite(ledRed, HIGH);
    //Green light OFF
    digitalWrite(ledGreen, LOW);
    //Buzzer ON
    tone(buzzer, 4000);
    delay(200);
    //Buzzer OFF
    noTone(buzzer);
    delay(100);
  }
   //Only Fire detection
  else if((digitalRead(FirePin) == HIGH) && (digitalRead(GasPin) == LOW))
  {
    //LCD Display for fire
    lcd.setCursor(0,0);
    lcd.print("Fire Detected!!!");
    //Red light ON
    digitalWrite(ledRed, HIGH);
    //Green light OFF
    digitalWrite(ledGreen, LOW);
    //Buzzer ON
    tone(buzzer, 4000);
    delay(200);
    //function call for Servo
    servo();
    //Buzzer OFF
    noTone(buzzer);
    delay(100);
  }
   //Both Gas and Fire Detection
  else if((digitalRead(GasPin) == HIGH) && (digitalRead(FirePin) == HIGH))
  { 
    // 1st LCD Display
    lcd.setCursor(0,0);
    lcd.print("Gas,Fire Detected"); 
    delay(200);
    //Red light ON
    digitalWrite(ledRed, HIGH);
    //Green light OFF
    digitalWrite(ledGreen, LOW);
    //Buzzer ON
    tone(buzzer, 5000);
    delay(200);
    //function call for Servo
    servo();
    //Clear and show 2nd LCD Display
    lcd.clear();
    lcd.print("Emergency Alert!!");
    //Red light OFF
    digitalWrite(ledRed, LOW);
    //Buzzer OFF
    noTone(buzzer);
    delay(100);
  }
   //All Clear or Safe Situation
  else if((digitalRead(FirePin) == LOW) && (digitalRead(GasPin) == LOW))
  {
    //LCD Display
    lcd.setCursor(0,0);
    lcd.print("Safe Now!");
    //Green light ON 
    digitalWrite(ledGreen, HIGH);
    //Red light OFF
    digitalWrite(ledRed, LOW);
  }
  delay(200);
  lcd.clear();
}

//fuction for Servo rotation
void servo() 
{
   //rotating servo anti-clockwise
  for(pos = 0; pos <= 90; pos = pos+2)
  {
    myServo.write(pos);
    delay(20);
  }
   //rotating servo clockwise
  for(pos = 90; pos >= 0; pos = pos-2)
  {
    myServo.write(pos); 
    delay(20);
  }
}
