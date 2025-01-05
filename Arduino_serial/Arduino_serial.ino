#include <SoftwareSerial.h>

#define RX_PIN 2
#define TX_PIN 3

SoftwareSerial mySerial(RX_PIN, TX_PIN); 

void setup() {
  Serial.begin(115200); 
  mySerial.begin(115200); 
}

void loop() {

  if (mySerial.available() > 0) {
    String received = mySerial.readStringUntil('\n'); 
    Serial.println(received); 
    Serial.println('\n');
  }
}
