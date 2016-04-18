<!--
title: Main Sketch (reading_sensors.ino)
summary: This document describes the code that we used for our project.
author: G. L. Clark, II
date Created: April 17, 2016
date Modified:{{ file.mtime }}
filename: sketch-temperature.md
-->

# Temperature Sketch (temperature.ino)

The ```temperature.ino``` sketch handles reading the temperature sensor. As with the humidity sketch, it also provides data to any client that requests it. Unlike the humidity sensor, there are different ways to present temperature values. In this sketch, we provide three(3): Celsius (the default), Fahrenheit and Kelvin.

```c++
// Libraries
#include "Arduino.h"

float getTempCelsius(void) {
  return hdc.readTemperature();
}

float getTempFahrenheit(void) {
  float currentTemp = hdc.readTemperature();
  return currentTemp * 9/5 + 32;
}

float getTempKelvin(void) {
  float currentTemp = hdc.readTemperature();
  return currentTemp + 273.15;
}

void handleTemperature() {
  String json = "";
  json += "{\"temperature\":{\"celsius\":";
  json += getTempCelsius();
  json += ",\"fahrenheit\":";
  json += getTempFahrenheit();
  json += ",\"kelvin\":";
  json += getTempKelvin();
  json += "}}";
  server.send ( 200, "application/json", json );
  json = String();
}

void handleTemperatureC() {
  String json = "";
  json += "{\"temperature\":{\"celsius\":";
  json += getTempCelsius();
  json += "}}";
  server.send ( 200, "application/json", json );
}

void handleTemperatureF() {
  String json = "";
  json += "{\"temperature\":{\"fahrenheit\":";
  json += getTempFahrenheit();
  json += "}}";
  server.send ( 200, "application/json", json );
}

void handleTemperatureK() {
  String json = "";
  json += "{\"temperature\":{\"kelvin\":";
  json += getTempKelvin();
  json += "}}";
  server.send ( 200, "application/json", json );
}

```

Since we are providing JSON data, it is easy send sensor readings to third party platforms. Platforms like [Adafuit IO](https://io.adafruit.com), [Loasant](https://www.losant.com/iot-platform) _(formally Structure?)_ and [PubNub](https://www.pubnub.com) will store and aggregate our data if we want it to. Interacting with these platforms are outside of the scope of our project. However, take the time to learn about them and decide which one best fits your needs.