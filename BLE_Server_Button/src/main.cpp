#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define BTN 18

BLEServer *pServer = NULL;
BLEService *pService = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;
uint8_t value = 0;
bool light = false;

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("device connected");
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("devise disconnected");
    deviceConnected = false;
  }
};

void setup()
{
  pinMode(BTN, INPUT);

  Serial.begin(115200);
  Serial.println("\nBLE Server starting");

  BLEDevice::init("BUTTON_SERVER");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE |
                                                                            BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop()
{
  if (deviceConnected)
  {
    if (digitalRead(BTN) == HIGH && !light)
    {
      light = true;
      value = 1;
      Serial.println("Button on");

      pCharacteristic->setValue(&value, 1);
      pCharacteristic->notify();
      delay(3);
    }

    if (digitalRead(BTN) == LOW && light)
    {
      light = false;
      value = 0;
      Serial.println("Button off");
      pCharacteristic->setValue(&value, 1);
      pCharacteristic->notify();
      delay(3);
    }
  }
}