#include "WiFi.h"
#include "AsyncUDP.h"

// THIS IS SERVER WITH LED!

const char *ssid = "Keenetic-0219";
const char *password = "EMGbmepp";

AsyncUDP udp;
const int port = 1234;

void printPacketData(AsyncUDPPacket packet);
void setupLed(String data);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  WiFi.disconnect();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  if (udp.listen(1234))
  {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length()); 
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      String myString = (const char *)packet.data();
      if (myString.startsWith("000"))
      {
        Serial.println("Dark");
        digitalWrite(LED_BUILTIN, LOW);
      }
      else if (myString.startsWith("111"))
      {
        Serial.println("Light");
        digitalWrite(LED_BUILTIN, HIGH);
      }
      packet.printf("Got %u bytes of data", packet.length());
    });
  }
}

void loop()
{
}
