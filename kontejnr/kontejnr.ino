#include <LiquidCrystal.h> //LCD library
#include<Servo.h> 
#include <Keypad.h>

#define echo 18
#define trig 17

Servo lid;
Servo compress;

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pointer=0;
const byte rows = 4; 
const byte columns = 4; 
char key[rows][columns] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinRows[rows] = {7, 6, 5, 4}; 
byte pinColumns[columns] = {3, 2, 1, 0}; 
Keypad keypad = Keypad( makeKeymap(key), pinRows, pinColumns, rows, columns );
int pos1, pos2, pos3, pos4;
int fotorezistor;
float  duration;
float  distance;
bool open;

void setup(){     
  lid.attach(15); 
  compress.attach(16);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
//  Serial.begin(9600);
  lcd.begin(16, 2); 
  
}
  
void loop(){
  fotorezistor = analogRead(A0);
 // Serial.println(fotorezistor);
  
 if(fotorezistor==595){
  password();
  }
  else{
  time_Measurement();
    distance = duration * (0.0343) / 2;
 // display_distance();
    capacity();
    container_lid();
  }
}


void time_Measurement(){ //function to measure the time taken by the pulse to return back
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
 /*   Serial.print("Distance in Cm: ");
    Serial.print(distance);
    Serial.println();
    lcd.print("Distance in Cm: ");*/
    lcd.setCursor(5, 1);
    lcd.print(distance);
    delay(1000);
   }

void container_lid(){
  if (fotorezistor !=595 && !open && distance<40 ){
    open = true;
    opencompressor();
    lcd.setCursor(0,1);
    lcd.print("Otevreno!");
    openservo();
    delay(3000) ; 
    
  }
  else{
    closeservo();
    lcd.setCursor(0,1);
    lcd.print("Zavreno!");
    delay(3000) ;
    closecompressor();
  }
 // delay(3000);
} 

void openservo(){
lid.write(0); 
    Serial.println(distance);  
    Serial.println("Open");
    open = false;
    delay(5000) ; 
    
}
void closeservo(){
  lid.write(90); 
    Serial.println(distance);
    Serial.println("Closed"); 
}
void opencompressor(){
  compress.write(0);
  delay(1000);
}

void closecompressor(){
  compress.write(90);
    delay(5000) ;
}

void capacity(){
  
  if(fotorezistor == 1021){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plnost: 0%");
  }
  if(fotorezistor > 1019 && fotorezistor <= 1020){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plnost: 25%");
  }
  if(fotorezistor > 1017 && fotorezistor <= 1019){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plnost: 50%");
  }
  if(fotorezistor > 595 && fotorezistor <= 1017){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plnost: 75%");
  }
  if(fotorezistor == 595){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plnost: 100%");
  }
   
  delay(100);
}

void password(){
   
  int digit1=1,digit2=5,digit3=7,digit4=8;
   lcd.setCursor(0,1);
   lcd.print("        ");
   char key = keypad.getKey();
   if (key){
    Serial.println(key);
   lcd.setCursor(8+pointer,1);
   lcd.print(key);
  // lcd.print("*");
   lcd.setCursor(8+pointer,1);
   key=key-48;
   pointer++; 
   switch(pointer){
    case 1:
    pos1=key; 
    break;
    case 2:
    pos2=key;  
    break;
    case 3:
    pos3=key;
    break;
    case 4:
    pos4=key;
   delay(50);
  if(pos1==digit1 && pos2==digit2 && pos3==digit3 && pos4==digit4){
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Odemknuto!");
    delay(3000); 
    lcd.clear();
    }
  else{
    Serial.println(key);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Spatny");
    lcd.setCursor(4,1);
    lcd.print("Heslo!");
    delay(1000);
    lcd.clear();
    }
   pointer=0;
   lcd.clear();

  break;
  }
 }
 if(!key){
   lcd.setCursor(0,0);
   lcd.print("Plno! heslo:");

 }

  delay(2);

}
