#include <Keypad.h>
#include <LiquidCrystal.h> //LCD library
#include<Servo.h> 

#define echo 4
#define trig 5

Servo servo1;
Servo servo2;

int QRD=0;
int valorsensor;

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {7,6,5,4}; 
byte colPins[COLS] = {3,2,1,0} ; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char key = keypad.getKey();
float  duration;
float  distance;
bool open;

void setup(){     
  servo1.attach(2); 
  servo2.attach(7);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  
}
  
void loop(){
 time_Measurement();
  distance = duration * (0.0343) / 2;
  display_distance();
  
  
  
  if (!open && distance<40 ){
    open = true;
    openservo();
    closekompresor();
    delay(3000) ; 
  }

  if (distance>40 ){
    closeservo();
    delay(3000) ;
    openkompresor();
  }

}
void time_Measurement()
  { //function to measure the time taken by the pulse to return back
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  
    duration = pulseIn(echo, HIGH);
  }
  void display_distance()
  { //function to display the distance on LCD/Serial Monitor
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.print("Distance in Cm: ");
    Serial.print(distance);
    Serial.println();
    lcd.print("Distance in Cm: ");
    lcd.setCursor(5, 1);
    lcd.print(distance);
    delay(1000);
   }

void openservo(){
servo1.write(0); 
    Serial.println(distance);  
    Serial.println("Open");
    open = false;
    delay(5000) ; 
    
}
void closeservo(){
  servo1.write(90); 
    Serial.println(distance);
    Serial.println("Closed"); 
}
void openkompresor(){
  servo2.write(0);
  delay(1000);
}

void closekompresor(){
  servo2.write(90);
    delay(5000) ;
}
