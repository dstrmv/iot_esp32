#include <WiFi.h>
#include <Arduino.h>

const char *ssid = "Keenetic-0219";
const char *password = "EMGbmepp";

WiFiServer server(8081);

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network

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
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

int value = 0;

void loop()
{
  WiFiClient client = server.available(); // listen for incoming clients

  if (client)
  {                                // if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte
        if (c == '1')
        {
          Serial.write(c);
          digitalWrite(LED_BUILTIN, HIGH); // GET /H turns the LED on
        }
        else if (c == '0')
        {
          Serial.write(c);
          digitalWrite(LED_BUILTIN, LOW); // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("\nClient Disconnected.");
  }
}