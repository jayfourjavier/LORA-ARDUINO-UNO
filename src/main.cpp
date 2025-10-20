// Receiver

#include <Arduino.h>
#include <SPI.h>
#include "LoRa.h"
#include <DHT.h>

#define DHT22_PIN 4
#define DHT_TYPE DHT22
#define SOIL_MOISTURE_PIN A0

DHT dht(DHT22_PIN, DHT_TYPE);

byte sensorNodeId = 3; // ID of this sensor node
float temperature = 0.0;
float humidity = 0.0;
float moisture = 0.0;

int zeroMoisture = 1023;      // Analog value for 0% moisture (dry soil)
int hundredMoisture = 0;      // Analog value for 100% moisture (wet soil)
int moistureSampleCount = 10; // Number of samples to average for soil moisture

String loraMessage()
{
  // S,<sensorNodeId>,<temperature>,<humidity>,<moisture>,E
  String message = "S," + String(sensorNodeId) + "," + String(temperature) + "," + String(humidity) + "," + String(moisture) + ",E";
  return message;
}

float readSoilMoisture()
{
  float _sensorValue = 0;
  float total = 0;
  for (int i = 0; i < moistureSampleCount; i++)
  {
    _sensorValue = analogRead(SOIL_MOISTURE_PIN);
    total += _sensorValue;
    delay(10); // Small delay between samples
  }
  float average = total / moistureSampleCount;
  // Map the average sensor value to a percentage (0% to 100%)
  float moisturePercent = map(average, zeroMoisture, hundredMoisture, 0, 100);
  return moisturePercent;
}

void readSensors()
{
  // Read DHT22 and validate before saving to global variables
  float _humidity = dht.readHumidity();
  float _temperature = dht.readTemperature();
  if (isnan(_humidity) || isnan(_temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {

    humidity = _humidity;
    temperature = _temperature;
  }
}

void setup()
{
  Serial.begin(9600);
  dht.begin();

  // Lora Module 433Mhz
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
  }
  else
  {
    Serial.println("LoRa Initializing OK!");
  }

  LoRa.setSyncWord(0xFF);
}

void printReadings()
{
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" %");
  moisture = readSoilMoisture();
  Serial.print(" | Soil Moisture: ");
  Serial.print(moisture);
  Serial.print(" %");
}

void submitReadings()
{
  String loraMsg = loraMessage();
  Serial.println(" | LoRa Msg: " + loraMsg);
  LoRa.beginPacket();
  LoRa.print(loraMsg);
  LoRa.endPacket();
}

void loop()
{
  readSensors();
  printReadings();
  submitReadings();
  delay(1000);
}
