// Libraries
#include "Arduino.h"

void handleTemperature() {
  String out = "";
  out += "[{\"currentTempC\":";
  out += hdc.readTemperature();
  out += "},{\"currentTempF\":";
  out += hdc.readTemperature() * 9/5 + 32;
  out += "}]";
  server.send ( 200, "application/json", out );
}

