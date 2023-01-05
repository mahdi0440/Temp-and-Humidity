#include <Arduino.h>
#include "HC05.h"
#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11

HC05 btSerial = HC05(8, 9);
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(9600); 
  btSerial.begin();
  btSerial.setBaud(9600);
  dht.begin();
}

void loop()
{
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  while (btSerial.connected())
  {
    if (btSerial.available())
    {
      if (isnan(t) || isnan(h))
      {
        btSerial.write("Failed to read from DHT sensor!");
      }
      else 
      {
        btSerial.write(t + ";" + h + ";");  
      }
    }
  }
}
