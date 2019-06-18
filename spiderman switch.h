#include <SoftwareSerial.h>
#include <Servo.h>

int righteyepin = 5;
int lefteyepin = 4;
Servo righteye;
Servo lefteye;
SoftwareSerial BTSerial (12,11); //RX||TX

int Button = 2;
int RightPower = 10;
int LeftPower = 7;
int state = HIGH;
int reading;
int glitch = 150;
int quick = 200;
int previous = LOW;
long time = 0;
long debounce = 200;
int value;
byte valueall[28];
char valuechar[28];
void setup() {

Serial.begin(9600);
BTSerial.begin(9600);
righteye.attach(righteyepin);
lefteye.attach(lefteyepin);
pinMode(Button, INPUT);
pinMode(RightPower, OUTPUT);  pinMode(LeftPower, OUTPUT);
Serial.println("AT commands: ");
righteyeopen();
lefteyeopen();

}

void loop() {
if (BTSerial.available()) {
value = BTSerial.parseInt();
Serial.print (value);
    }
switch (value) {
  case 1:
      digitalWrite(RightPower, HIGH);  
      righteye.write(120);
      delay (1000);
      digitalWrite(RightPower, LOW); 
    break;
  case 2:
      digitalWrite(RightPower, HIGH);  
      righteye.write(30);
      delay (1000);
      digitalWrite(RightPower, LOW); 
    break;
  case 3:
      digitalWrite(LeftPower, HIGH);  
      lefteye.write(70);
      delay (1000);
      digitalWrite(LeftPower, LOW);  
    break;	
  case 4:
      digitalWrite(LeftPower, HIGH);  
      lefteye.write(180);
      delay (1000);
      digitalWrite(LeftPower, LOW);   
    break;	
  case 5:
      digitalWrite(LeftPower, HIGH);  
      digitalWrite(RightPower, HIGH);  
      lefteye.write(180);
      righteye.write(30);
      delay (1000);
      digitalWrite(LeftPower, LOW); 
      digitalWrite(RightPower, LOW);  
    break;
  case 6:
      digitalWrite(LeftPower, HIGH);  
      digitalWrite(RightPower, HIGH);  
      lefteye.write(70);
      righteye.write(120);
      delay (1000);
      digitalWrite(LeftPower, LOW); 
      digitalWrite(RightPower, LOW); 
    break;
  case 7:
botheyeopen();
delay (200);
lefteyeclosed();
delay (200);
lefteyeopen();
righteyeclosed();
delay (200);
lefteyeclosed();
delay (100);
botheyeopen(); 
delay (500);
lefteyeclosed();
delay (200);
lefteyeopen();
righteyeclosed();
delay (200);
lefteyeclosed();
delay (100);
botheyeopen();    
    break;
  case 8:
botheyeclosed();
delay (4000);
botheyeopen();   
    break;
  case 9:
digitalWrite(RightPower, HIGH);
righteye.write(120);
delay (glitch);
righteye.write(30);
delay (glitch);  
righteye.write(120);
delay (glitch);
righteye.write(30);
delay (glitch); 
righteye.write(120);
delay (glitch);
righteye.write(30);
delay (glitch); 
digitalWrite(RightPower, LOW);   
    break;
  case 10:
digitalWrite(RightPower, HIGH);
digitalWrite(LeftPower, HIGH);
righteye.write(120);
lefteye.write(70);
delay (glitch);
righteye.write(30);
lefteye.write(180);
delay (glitch);  
righteye.write(120);
lefteye.write(70);
delay (glitch);
righteye.write(30);
lefteye.write(180);
delay (glitch); 
righteye.write(120);
lefteye.write(70);
delay (glitch);
righteye.write(30);
lefteye.write(180);
delay (glitch); 
digitalWrite(RightPower, LOW); 
digitalWrite(LeftPower, LOW);  
    break;
}

sideButton();
}

void sideButton(){
   reading = digitalRead(Button);

  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH) {
      state = LOW; 
      digitalWrite(RightPower, HIGH);
      digitalWrite(LeftPower, HIGH);
      righteye.write(120);
      lefteye.write(70);
      delay (1000);
      digitalWrite(RightPower, LOW);
      digitalWrite(LeftPower, LOW);
    }
    else {
      state = HIGH;
      digitalWrite(RightPower, HIGH);
      digitalWrite(LeftPower, HIGH);
      righteye.write(30);
      lefteye.write(180);
      delay (1000);
      digitalWrite(RightPower, LOW);
      digitalWrite(LeftPower, LOW);
    }
    time = millis();
  }

  previous = reading;
 
}

void lefteyeopen(){
digitalWrite(LeftPower, HIGH);
lefteye.write(180);  
delay (300);
digitalWrite(LeftPower, LOW);
}

void lefteyeclosed(){
digitalWrite(LeftPower, HIGH);
lefteye.write(70);
delay (300);
digitalWrite(LeftPower, LOW);
}

void righteyeopen(){
digitalWrite(RightPower, HIGH);
righteye.write(30);
delay (quick);
digitalWrite(RightPower, LOW);
}

void righteyeclosed(){
digitalWrite(RightPower, HIGH);
righteye.write(120);
delay (quick);
digitalWrite(RightPower, LOW);
}

void botheyeclosed(){
      digitalWrite(LeftPower, HIGH);  
      digitalWrite(RightPower, HIGH);  
      lefteye.write(70);
      righteye.write(120);
      delay (1000);
      digitalWrite(LeftPower, LOW); 
      digitalWrite(RightPower, LOW);
}
void botheyeopen(){
      digitalWrite(LeftPower, HIGH);  
      digitalWrite(RightPower, HIGH);  
      lefteye.write(180);
      righteye.write(30);
      delay (1000);
      digitalWrite(LeftPower, LOW); 
      digitalWrite(RightPower, LOW);
}