#include<SPI.h>

#define SS PA4
#define buzzerPin PB9
#define ledPin PC13
#define buttonPin PA0

void setup (void)
{
pinMode(SS, OUTPUT);
pinMode(ledPin, OUTPUT);
pinMode(buttonPin, INPUT);
pinMode(buzzerPin, OUTPUT);
SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV16);
digitalWrite(SS, HIGH);
digitalWrite(ledPin, LOW);
}

void loop(void)
{
int masterSend, masterReceive;

masterSend = digitalRead(buttonPin);

digitalWrite(SS, LOW);

masterReceive = SPI.transfer(masterSend);
delay(500);
digitalWrite(SS, HIGH);

if (masterReceive == HIGH)
{
digitalWrite(ledPin, HIGH);
digitalWrite(buzzerPin, LOW);
}
else
{
digitalWrite(ledPin, LOW);
digitalWrite(buzzerPin, HIGH);

}
}