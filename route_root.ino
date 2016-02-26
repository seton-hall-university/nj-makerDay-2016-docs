// Libraries
#include "Arduino.h"

void handleRoot() {
 digitalWrite ( ledWiFi, 0 );
  char temp[1024];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  // Convert the floats to strings
  char tc[6];
  char tf[6];
  char hm[6];
  dtostrf(getTempCelsius(), 3, 2, tc);
  dtostrf(getTempFahrenheit(), 3, 2, tf);
  dtostrf(getHumidityRH(), 3, 2, hm);

  snprintf ( temp, 1024,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Temp/Humidity Sensors</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p><strong>Uptime</strong>: %02d:%02d:%02d</p>\
    <p><strong>Celsius</strong>: %s C</p>\
    <p><strong>Fahrenheit</strong>: %s F</p>\
    <p><strong>Humidity</strong>: %s RH</p>\
  </body>\
</html>",

    hr, min % 60, sec % 60, tc, tf, hm
  );
  server.send ( 200, "text/html", temp );
  digitalWrite ( ledWiFi, 1 );
}
