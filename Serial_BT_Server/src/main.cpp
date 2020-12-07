#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial BTSerial;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  BTSerial.begin("ESP32_LED");
  Serial.println("Device started");
}

void loop()
{
  if (BTSerial.available()) {
    char r = BTSerial.read();
    if (r == '1') {
      digitalWrite(LED_BUILTIN, HIGH);
    } else if (r == '0') {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}