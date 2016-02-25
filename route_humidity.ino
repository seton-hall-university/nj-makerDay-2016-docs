// Libraries
#include "Arduino.h"

void handleHumidity() {
  String out = "";
  out += "[{\"currentHumidity\":";
  out += hdc.readHumidity();
  out += "}]";
  server.send ( 200, "application/json", out );
}
