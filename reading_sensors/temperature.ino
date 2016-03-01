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
  String out = "";
  out += "{\"temperature\":{\"celsius\":";
  out += getTempCelsius();
  out += ",\"fahrenheit\":";
  out += getTempFahrenheit();
  out += ",\"kelvin\":";
  out += getTempKelvin();
  out += "}}";
  server.send ( 200, "application/json", out );
}

void handleTemperatureC() {
  String out = "";
  out += "{\"temperature\":{\"celsius\":";
  out += getTempCelsius();
  out += "}}";
  server.send ( 200, "application/json", out );
}

void handleTemperatureF() {
  String out = "";
  out += "{\"temperature\":{\"fahrenheit\":";
  out += getTempFahrenheit();
  out += "}}";
  server.send ( 200, "application/json", out );
}

void handleTemperatureK() {
  String out = "";
  out += "{\"temperature\":{\"kelvin\":";
  out += getTempKelvin();
  out += "}}";
  server.send ( 200, "application/json", out );
}

