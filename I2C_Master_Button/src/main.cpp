#include <Arduino.h>
#include <Wire.h>
#include <WirePacker.h>

const int BTN = 18;
const int SLAVE_ADDR = 9;

void setup()
{
  Wire.begin(21, 22);
  pinMode(BTN, INPUT);
  Serial.begin(115200);
  delay(500);
}

byte condition = 0;

void loop()
{
  delay(50);

  WirePacker packer;

  if (digitalRead(BTN) == HIGH && condition == 0)
  {
    Serial.println("Button on");
    condition = 1;
    packer.write(condition);
    packer.end();
    Wire.beginTransmission(SLAVE_ADDR);
    
    while (packer.available())
    { // write every packet byte
      Wire.write(packer.read());
    }
    Wire.endTransmission();
  }

  if (digitalRead(BTN) == LOW && condition == 1)
  {
    Serial.println("Button off");
    condition = 0;
    packer.write(condition);
    packer.end();
    Wire.beginTransmission(SLAVE_ADDR);
    while (packer.available())
    { // write every packet byte
      Wire.write(packer.read());
    }
    Wire.endTransmission();
  }
}
