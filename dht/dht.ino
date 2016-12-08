#define BLYNK_PRINT Serial  
#include <SPI.h>
#include <SimpleTimer.h>
#include <DHT.h>

#define DHTPIN 4   
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V9, t);
  Blynk.virtualWrite(V10, h);
}

void setup()
{

  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}

