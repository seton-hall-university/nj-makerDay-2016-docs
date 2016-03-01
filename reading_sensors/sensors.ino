// Libraries
#include "Arduino.h"


void handleSensors() {
  String out = "";
  out += "{\"sensors\":";
  out += "{\"humidity\":{\"relative\":";
  out += getHumidityRH();
  out += "},";
  out += "{\"temperature\":{\"celsius\":";
  out += getTempCelsius();
  out += ",\"fahrenheit\":";
  out += getTempFahrenheit();
  out += ",\"kelvin\":";
  out += getTempKelvin();
  out += "}}";
  out += "}";
  server.send ( 200, "application/json", out );
}
