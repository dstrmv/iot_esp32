#include <Arduino.h>
#include <BluetoothSerial.h>

const int BTN = 18;
BluetoothSerial BTSerial;
bool light = false;

void setup() {
  pinMode(BTN, INPUT);
  Serial.begin(115200);
  BTSerial.begin("ESP32_BUTTON", true);
  bool connected = BTSerial.connect("ESP32_LED");
  if (connected) {
    Serial.println("BT Client connected");
  }

}

void loop() {

  if (digitalRead(BTN) == HIGH && !light) {
    light = true;
    BTSerial.write('1');
  } else if (digitalRead(BTN) == LOW && light) {
    light = false;
    BTSerial.write('0');
  }

  // put your main code here, to run repeatedly:
}