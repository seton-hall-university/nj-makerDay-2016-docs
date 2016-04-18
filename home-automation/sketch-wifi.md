<!--
title: Main Sketch (reading_sensors.ino)
summary: This document describes the code that we used for our project.
author: G. L. Clark, II
date Created: April 17, 2016
date Modified:{{ file.mtime }}
filename: sketch-temperature.md
-->

# WiFi Sketch (wifi.ino)

The ```wifi.ino``` sketch handles connecting the ESP8266 to an existing WiFi network. If the ESP8266 cannot connect to one of the pre-programmed access points, then it will create one of it's own. As with some of the other sketches, parts of this sketch can be attributed to either official examples or resources on the internet.

```c++
// Libraries
#include "Arduino.h"

void connectWiFi() {
  wifiMulti.addAP(ssid1, password1);        //if you have less SSID, delete the others
  wifiMulti.addAP(ssid2, password2);
  wifiMulti.addAP(ssid3, password3);

  Serial.println("Connecting WiFi...");

//  while (wifiMulti.run() != WL_CONNECTED) {
    for(int x = 0; x < 10; x++) {
      wifiMulti.run();
//      Serial.println(WiFi.status());
      
      if (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting...");
  
        // If we don't connect after x tries, create our own AP.
        if ( x == 9) {
          createAccessPoint();
          break;
        }
      } else {
        digitalWrite ( ledWiFi, 1 );
        Serial.println( "\nWiFi Connected" );
        getWiFiAddress();
        break;
      }
      
      Serial.println(x);
    }
//  }
}

char getWiFiAddress(void) {
  // Print the IP address out to the serial connection
  //  Serial.print ( "\n\nIP address: " );
  //  Serial.println ( WiFi.localIP() );

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm\n");

  return WiFi.localIP();
}

void createAccessPoint() {
  // Reference: ESP8266 WiFiAccessPoint Example.
  Serial.println();
  Serial.println("Configuring Access Point...");
//  Serial.println("webdev-esp8266-" + chipID);
  
  WiFi.softAP("WebDev-ESP8266-003");
//  WiFi.softAP("webdev-esp8266-" + chipID);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  Serial.println();
  digitalWrite ( ledWiFi, 1 );
  Serial.print("Access Point configured.");
}
```