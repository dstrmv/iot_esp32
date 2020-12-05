#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>

int rd;

void receiveEvent(int a);

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  WireSlave.begin(21, 22, 9);
  WireSlave.onReceive(receiveEvent);
  Serial.begin(115200);
  Serial.println("I2C Slave Demonstration");
}

void receiveEvent(int a)
{
  rd = WireSlave.read();
  Serial.println(rd);
  if (rd == 1)
  {
    digitalWrite(BUILTIN_LED, HIGH);
  }
  else
  {
    digitalWrite(BUILTIN_LED, LOW);
  }
}

void loop()
{
  WireSlave.update();
  delay(1);

  // put your main code here, to run repeatedly:
}