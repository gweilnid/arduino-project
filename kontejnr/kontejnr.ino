#include <LiquidCrystal.h> 
#include<Servo.h> 

#define echo 18
#define trig 17

Servo servo1;
Servo servo2;

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int valorsensor;
float  duration;
float  distance;
bool open;

void setup(){     
  servo1.attach(15);  
  servo2.attach(16);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  
}
  
void loop(){
  
  time_Measurement();
    distance = duration * (0.0343) / 2;
 // display_distance();
    valorsensor = analogRead(0);
    Serial.println(valorsensor);
    capacity();
    container_lid();
  
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
void display_distance(){ //function to display the distance on LCD/Serial Monitor
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

void container_lid(){
  if (valorsensor !=595 && !open && distance<40 ){
    open = true;
    openkompresor();
    lcd.setCursor(1,1);
    lcd.print("Otevreno!");
    openservo();
    delay(3000) ; 
    
  }
  else{
    closeservo();
    lcd.setCursor(1,1);
    lcd.print("Zavreno!");
    delay(3000) ;
    closekompresor();
  }

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

void capacity(){
  if(valorsensor == 1021){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Plnost: 0%");
  }
  if(valorsensor > 1019 && valorsensor <= 1020){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Plnost: 25%");
  }
  if(valorsensor > 1017 && valorsensor <= 1019){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Plnost: 50%");
  }
  if(valorsensor > 595 && valorsensor <= 1017){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Plnost: 75%");
  }
  if(valorsensor == 595){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Plnost: 100%");
  }
}
