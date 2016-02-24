#include "Arduino.h"
#include "Adafruit_HDC1000.h"
#include <Wire.h>

Adafruit_HDC1000 hdc = Adafruit_HDC1000();

const int hdc_sda = 14;
const int hdc_scl = 2;

float currentTempC = 0.00;
float currentTempF = 32.00;

void drawTempGraph() {
 String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"blue\">\n";
  int y = hdc.readTemperature();
  for (int x = 10; x < 390; x+= 10) {
    int y2 = rand() % 100;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send ( 200, "image/svg+xml", out);
}

void setupMonitor() {

  Serial.println("HDC100x test");
  // Set SDA and SDL ports
  Wire.begin(hdc_sda, hdc_scl);
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  
}

void readMonitors() {  
//  Serial.print("Temp: "); Serial.print(hdc.readTemperature());
//  Serial.print("\t\tHum: "); Serial.println(hdc.readHumidity());
//  delay(1000);
  currentTempC = hdc.readTemperature();
  currentTempF = currentTempC * 9/5 + 32;
  
  Serial.print("Temp: "); 
  Serial.print(hdc.readTemperature());
  Serial.print("C / ");
  Serial.print(hdc.readTemperature() * 9/5 + 32);
  Serial.print("F"); 
  Serial.print("\tHum: "); 
  Serial.println(hdc.readHumidity());
  delay(3000);
}
