/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */
#include <Arduino.h>
#include <WiFi.h>

const int BTN = 18;
bool light = false;

const char *ssid = "Keenetic-0219";
const char *password = "EMGbmepp";

const char *host = "192.168.1.53";
WiFiClient client;
bool connected = false;

void connectWiFi();

void connectWiFi()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup()
{
    pinMode(BTN, INPUT);
    Serial.begin(115200);
    delay(10);

    connectWiFi();
    // We start by connecting to a WiFi network
}

void loop()
{
    // Use WiFiClient class to create TCP connections
    if (!client.connected())
    {
        client.stop();
        Serial.print("connecting to ");
        Serial.println(host);
        
        connected = client.connect(host, 8081);
        if (connected)
        {
            Serial.println("Client connected");
        }
        else
        {
            Serial.println("Connection failed");
            delay(500);
        }
    }

    while (client.connected() && WiFi.isConnected())
    {
        if (digitalRead(BTN) == HIGH && !light)
        {
            light = true;
            Serial.println("Button on");
            client.write("1");
        }

        if (digitalRead(BTN) == LOW && light)
        {
            light = false;
            Serial.println("Button off");
            client.write("0");
        }

        delay(10);
    }

    delay(10);
}
