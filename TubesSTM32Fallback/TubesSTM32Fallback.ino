HardwareSerial Serial1(PA10, PA9);
#include <Servo.h>

Servo servogue;
const int pinservo = PA2;
  int angle;

#define trigger PA0
#define echo PA1
#define buzzer PB9
#define sensorsuara PA3
#define tombolswitch PA4

unsigned long jarakterakhir = 0;
const unsigned long intervaljarak = 50; 
float jarak = 0.0;

volatile bool statustutuptong = false; 

void ISRtombol();

void setup() {
  pinMode(sensorsuara, INPUT);
  servogue.attach(pinservo);
  servogue.write(90);

   pinMode(tombolswitch, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(tombolswitch), ISRtombol, FALLING);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(buzzer, LOW);
  Serial1.begin(115200);
}

void loop() {
  int nilaisensorsuara = digitalRead(sensorsuara); 

  if (millis() - jarakterakhir >= intervaljarak) {
    jarakterakhir = millis();
    jarak = ukurjarak();
  }

  if ((jarak < 20.0 && jarak > 0.0) || nilaisensorsuara == 1) {
     statustutuptong = true;
  }

  if (statustutuptong==true) {
    Serial1.println("Membuka tong sampah...");
    statustutuptong=false;
    
    tone(buzzer, 400); 
    delay(200);

    tone(buzzer, 660); 
    delay(200);

    tone(buzzer, 2000); 
    delay(400);

    noTone(buzzer);
    digitalWrite(buzzer, LOW);

    for(angle = 90; angle > 10; angle--)    
      {                                
      servogue.write(angle);           
      delay(15);      
      } 
    delay(3000);

    Serial1.println("Menutup tong sampah...");
    angle=10;  
    
    tone(buzzer, 1000); 
    delay(400);

    tone(buzzer, 600); 
    delay(300);

    tone(buzzer, 400); 
    delay(400);
    
    noTone(buzzer);
    digitalWrite(buzzer, LOW);

    for(angle = 10; angle < 90; angle++)  
      {                                  
      servogue.write(angle);               
      delay(15);                
      }
    
    delay(1000);
  }

}

float ukurjarak() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  long duration = pulseIn(echo, HIGH, 30000); 
  if (duration == 0) return -1; 
  return (duration * 0.0343) / 2; 

}

void ISRtombol() {
  statustutuptong = !statustutuptong; 
}