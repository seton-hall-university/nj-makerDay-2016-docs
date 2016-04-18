<!--
title: Main Sketch (reading_sensors.ino)
summary: This document describes the code that we used for our project.
author: G. L. Clark, II
date Created: April 17, 2016
date Modified:{{ file.mtime }}
filename: sketch-humidity.md
-->

# Humidity Sketch (humidity.ino)

The ```humidity.ino``` sketch handles reading the humidity sensor. It also provides that data to any client requesting it. 

```c++
// Libraries
#include "Arduino.h"

float getHumidityRH(void) {
  return hdc.readHumidity();
}

void handleHumidity() {
  String json = "";
  json += "{\"humidity\":{\"relative\":";
  json += getHumidityRH();
  json += "}}";
  server.send ( 200, "application/json", json );
}
```

Since we are providing JSON data, it is easy send sensor readings to third party platforms. Platforms like [Adafuit IO](https://io.adafruit.com), [Loasant](https://www.losant.com/iot-platform) _(formally Structure?)_ and [PubNub](https://www.pubnub.com) will store and aggregate our data if we want it to. Interacting with these platforms are outside of the scope of our project. However, take the time to learn about them and decide which one best fits your needs.