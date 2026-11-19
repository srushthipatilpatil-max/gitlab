#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient w;
PubSubClient m(w);

void callback(char* topic, byte* payload, unsigned int length)
{
  if (length >= 2 && payload[0] == '0' && payload[1] == 'N')
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
  }
}

void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  WiFi.begin("Akash","123456789");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  m.setServer("broker.emqx.io", 1883);
  m.setCallback(callback);

  while (!m.connected())
  {
    m.connect("ESP8266_01");
    delay(500);
  }

  m.subscribe("Akash");
}

void loop()
{
  m.loop();
}
