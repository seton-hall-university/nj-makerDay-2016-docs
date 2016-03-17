<!--
title: NodeMCU DevKit
summary: This document describes the NodeMCU DevKit.
author: G. L. Clark, II
date Created: March 16, 2016
date Modified:{{ file.mtime }}
filename: nodemcu-devkit.md
-->

# NodeMCU DevKit

The Development Kit is an open-source firmware and development platform that helps prototype your IOT product within a few lines of Lua script[^1]. Based on the ESP8266[^2], it integrates GPIO, PWM, I2C, 1-Wire and ADC all in one board.

<figure>
<img src="http://www.esp8266.com/wiki/lib/exe/fetch.php?cache=&media=12-01.jpg" alt="ESP8266 ESP-12" height="350">
<figcaption>ESP8266 ESP-12, the heart of the NodeMCU DevKit</figcaption>
</figure>

Even though there are many ways to program the NodeMCU, we will be using the Arduino Software (IDE)[^3]. This IDE is simple to use and makes "flashing" the DevKit easy. We will tell our Arduino based board what to do by writing code in the IDE. The Arduino programming language is similar to C or C++ and is easy to learn.

<figure>
<img src="https://www.arduino.cc/en/uploads/Guide/Arduino1Blink.png" alt="Arduino Blink Sketch" height="350">
<figcaption>Arduino Software IDE</figcaption>
</figure>


#### References

[^1]: https://nodemcu.com/index_en.html
[^2]: http://www.esp8266.com/wiki
[^3]: https://www.arduino.cc/en/Main/Software