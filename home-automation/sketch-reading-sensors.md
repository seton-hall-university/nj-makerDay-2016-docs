<!--
title: Main Sketch (reading_sensors.ino)
summary: This document describes the code that we used for our project.
author: G. L. Clark, II
date Created: April 17, 2016
date Modified:{{ file.mtime }}
filename: sketch-reading-sensors.md
-->

# Main Sketch (reading_sensors.ino)

As mentioned previously, the main sketch sets up the program. At the time of this writing, it contains:

 * The libraries that we will use
 * Variable definitions used throughout the program
 * Generic functions 
 * The Arduino ```setup()``` and ```loop()``` fuctions

Feel free to remove any part of the sketch that you will not be using. 

## Libraries

At a minimum, we will need the following libraries:

```c++
// Libraries
#include "Arduino.h"
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include "Adafruit_HDC1000.h"
#include <Wire.h>
```
## Variables and Functions

The minimum variable definitions that are need are:

 * Your WiFi information
 * The ports where the HDC is connected
 * The DNS name you are calling your NodeMCU unit

Depending on your configuration, these values should change. Be sure to provide at least one(1) WiFi access point to connect to. If not, the program will create a default one for you. We'll review that part of the program in the ```wifi.ino``` sketch. We'll also define the functions that we'll use through out the program.

```c++
// Variable Definitions
const int hdc_sda = 14; // SDA port for the HDC1000
const int hdc_scl = 2; // SCL port for the HDC1000
const char *dnsName = "webdev-esp8266-03"; // DNS Name

// Set WiFi constants
const char* ssid1     = "ssid1";
const char* password1 = "password1";
// const char* ssid2     = "ssid2";
// const char* password2 = "password2";
// const char* ssid3     = "ssid3";
// const char* password3 = "password13";
...
```

## The setup() Function

The next part of the main sketch is the ```setup()``` function. It's called when a sketch starts and is used to initialize variables, pin modes, start using libraries, etc. This function will only run once, after each power-up or reset of the Arduino board[^1].

```c++
// Sketch Code
void setup ( void ) {
  pinMode ( ledWiFi, OUTPUT );
  Serial.begin ( 115200 );

  Serial.print("\nChip ID = ");
  Serial.print(ESP.getChipId());
  Serial.println("");

  // Check File Mounts
  checkMount();

  // Connect to Wifi
  connectWiFi();

  Serial.println("\nSetting up HDC100x...");
  Wire.begin(hdc_sda, hdc_scl);
  if (!hdc.begin()) {
    Serial.println("\nCouldn't find sensor!");
    while (1);
  }
  ...
  ```
  
The ```setup()``` function also tells our web server what to serve when certain URIs are requested.

  ```c++
  ...
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
}
```

## The loop() Function

The last part of the main sketch is the ```loop()``` function. It loops consecutively, allowing the program to change and respond[^2] to incoming requests. In our case, we're telling the web server we've setup on the ESP8266 to handle client requests.

```c++
void loop ( void ) {
  server.handleClient();
}
```

#### References

[^1]: http://www.arduino.cc/en/Reference/Setup
[^2]: http://www.arduino.cc/en/Reference/Loop