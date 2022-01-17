/*
 * Greenhouse Arduino Sketch
 */
 
#include "DHT.h"

// Digital pin for DHT11 Temperature and Humidity Sensor
#define DHTPIN 2     
#define DHTTYPE DHT11

DHT TempAndHumidity(DHTPIN, DHTTYPE); // Initialize DHT sensor.

const int timeDelay = 10000;          // Time delay between readings (1000 = 1sec)

void setup() 
{
  Serial.begin(9600);

  TempAndHumidity.begin();
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(timeDelay);

  CheckTempAndHumidity();

  
}

void CheckTempAndHumidity()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old'
  float humidity = TempAndHumidity.readHumidity();
  // Read temperature as Celsius (the default)
  float tempC = TempAndHumidity.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float tempF = TempAndHumidity.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float heatIndexF = TempAndHumidity.computeHeatIndex(tempF, humidity);
  // Compute heat index in Celsius (isFahreheit = false)
  float heatIndexC = TempAndHumidity.computeHeatIndex(tempC, humidity, false);

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempC);
  Serial.print(F("°C "));
  Serial.print(tempF);
  Serial.print(F("°F  Heat index: "));
  Serial.print(heatIndexC);
  Serial.print(F("°C "));
  Serial.print(heatIndexF);
  Serial.println(F("°F"));
}
