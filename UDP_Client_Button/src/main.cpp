#include "WiFi.h"
#include "AsyncUDP.h"

const char *ssid = "Keenetic-0219";
const char *password = "EMGbmepp";

const int BTN = 18;
bool connected = false;
bool light = false;

AsyncUDP udp;

void setup()
{
    pinMode(BTN, INPUT);
    Serial.begin(115200);
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed");
        while (1)
        {
            delay(1000);
        }
    }

    connected = udp.connect(IPAddress(192, 168, 1, 53), 1234);
    delay(500);
}

void loop()
{
    delay(1);
    if (digitalRead(BTN) == HIGH && !light)
    {
        Serial.println("Btn on");
        light = true;
        if (connected)
        {
            udp.print("111");
        }
    }

    if (digitalRead(BTN) == LOW && light)
    {
        Serial.println("Btn off");
        light = false;
        if (connected)
        {
            udp.print("000");
        }
    }

    delay(1);
}