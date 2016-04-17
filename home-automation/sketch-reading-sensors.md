<!--
title: Main Sketch (reading_sensors.ino)
summary: This document describes the code that we used for our project.
author: G. L. Clark, II
date Created: April 17, 2016
date Modified:{{ file.mtime }}
filename: sketch-reading-sensors.md
-->

# Main Sketch (reading_sensors.ino)

As mentioned previously, the main sketch sets up the program. At the time of this writing, it contains

``` c++
// Libraries
#include "Arduino.h"
#include <ArduinoJson.h>
#include "FS.h"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Adafruit_HDC1000.h"
#include <Wire.h>

Adafruit_HDC1000 hdc = Adafruit_HDC1000(); // Create a class for the HDC Sensor
ESP8266WebServer server ( 80 ); // Create an ESP8266 Server class
ESP8266WiFiMulti wifiMulti; // Create an ESP8266 Multi WiFi class
WiFiClient client; // Create an ESP8266 WiFiClient class.
WiFiClientSecure sslclient;

#define DBG_OUTPUT_PORT Serial

// Variable Definitions
const int hdc_sda = 14; // SDA port for the HDC1000
const int hdc_scl = 2; // SCL port for the HDC1000
const int ledWiFi = 16; // LEDs are going to be used.
const char chipID = ESP.getChipId(); // The ESP's Chip ID
const char *dnsName = "webdev-esp8266-" + chipID; // DNS Name

// Set WiFi constants
const char* ssid1     = "theNile";
const char* password1 = "stereo!3";
const char* ssid2     = "@400SoAve#";
const char* password2 = "589ShU!$305";
const char* ssid3     = "MiFi4620L Jetpack B1A7 Secure";
const char* password3 = "060388d1";

// Functions
void setupDNS(void);
void connectWiFi(void);
char getWiFiAddress(void);
//void sendWiFiAddress(void);
void handleRoot();
void handleSensors();
void handleNotFound();
void handleTemperature();
void handleTemperatureC();
void handleTemperatureF();
void handleTemperatureK();
void handleHumidity();
float getTempCelsius(void);
float getTempFahrenheit(void);
float getTempKelvin(void);
float getHumidityRH(void);
bool loadIndex(void);
void loadStatus(void);
bool handleFileRead(String path);
void handleFileList(void);
bool checkMount(void);
void createAccessPoint(void);

// Sketch Code
void setup ( void ) {
  pinMode ( ledWiFi, OUTPUT );
  //  digitalWrite ( ledWiFi, 1 );
  Serial.begin ( 115200 );

  Serial.print("\nChip ID = ");
  Serial.print(ESP.getChipId());
  Serial.println("");

  // Check File Mounts
  checkMount();

  // Connect to Wifi
  connectWiFi();

  // Setup mDNS
//  setupDNS();

  // Send the WiFi address out.
  // NOTE: This isn't sending the IP, just a <blank>
  // sendWiFiAddress();

  Serial.println("\nSetting up HDC100x...");
  Wire.begin(hdc_sda, hdc_scl);
  if (!hdc.begin()) {
    Serial.println("\nCouldn't find sensor!");
    while (1);
  }

  server.on ( "/", HTTP_GET, handleRoot );
  server.on ( "/file", HTTP_GET, loadIndex );
  server.on ( "/status", HTTP_GET, loadStatus );
  server.on("/list", HTTP_GET, handleFileList);
  server.on ( "/sensors", HTTP_GET, handleSensors );
  server.on ( "/temperature", HTTP_GET, handleTemperature );
  server.on ( "/temperature/celsius", HTTP_GET, handleTemperatureC );
  server.on ( "/temperature/fahrenheit", HTTP_GET, handleTemperatureF );
  server.on ( "/temperature/kelvin", HTTP_GET, handleTemperatureK );
  server.on ( "/humidity", HTTP_GET, handleHumidity );
  server.on ( "/test", HTTP_GET, []() {
    server.send ( 200, "text/plain", "<p>this works as well</p>" );
  } );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "\nHTTP server started" );

  //  digitalWrite ( ledWiFi, 0 );
}

void loop ( void ) {
  //  digitalWrite ( ledWiFi, 0 );
  server.handleClient();

  //
  //  getWiFiAddress();
  //
  //  Serial.print("Temp: ");
  //  Serial.print(getTempCelsius());
  //  Serial.print("C / ");
  //  Serial.print(getTempFahrenheit());
  //  Serial.print("F");
  //  Serial.print("\tHum: ");
  //  Serial.println(getHumidityRH());
  //
  ////  digitalWrite ( ledWiFi, 1 );
  ////  delay(180000); // 3 minutes
  ////  delay(30000); // 30 seconds
  //  delay(500); // .5 seconds
}
```