// Libraries
#include "Arduino.h"

float getHumidityRH(void) {
  return hdc.readHumidity();
}

void handleHumidity() {
  String out = "";
  out += "{\"humidity\":{\"relative\":";
  out += hdc.readHumidity();
  out += "}}";
  server.send ( 200, "application/json", out );
}
