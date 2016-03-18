<!--
title: Temperature & Humidity Sensors
summary: This document completely plagerizes Adafruit's content.
author: Adafruit.com
date Created: March 17, 2016
date Modified:{{ file.mtime }}
filename: sensors.md
-->

# Temperature & Humidity Sensors

The sensors that we will be using in our project are either the [Adafruit HDC1008](https://www.adafruit.com/products/2635) or the Dallas DS18B20. The HDC1008 will measure both temperature and humidity while the DS18B20 only read temperature.

## Adafruit HDC1008 

This I2C digital humidity sensor is a fairly accurate and intelligent alternative to the much simpler [Humidity and Temperature Sensor - SHT15 Breakout](https://www.adafruit.com/products/1638). <img src="https://cdn-shop.adafruit.com/970x728/2635-01.jpg" style="float:right; margin:5px 0 5px 5px; width:300px"> It has a typical accuracy of ±4% with an operating range that's optimized from 10% to 80% relative humidity (RH). Operation outside this range is still possible - just the accuracy might drop a bit. The temperature output has a typical accuracy of ±0.2°C from -20 ~ 85°C.

The HDC1008 sensor chip has 2 address-select pins, so you can have up to 4 shared on a single I2C bus. It's also 3-5V power and logic safe so you don't need any level shifters or regulators to use with a 5V or 3V micro-controller.

Such a lovely chip, but only available in a tiny BGA package. So we spun up a breakout board with the chip and some extra passive components to make it easy to use. Each order comes with one fully assembled and tested PCB breakout and a small piece of header. You'll need to solder the header onto the PCB but it's fairly easy and takes only a few minutes even for a beginner.

## DS18B20 Digital Temperature Sensor

These 1-wire digital temperature sensors are fairly precise (±0.5°C over much of the range). They can give up to 12 bits of precision from the on board digital-to-analog converter. They work great with any micro-controller using a single digital pin. You can even connect multiple ones to the same pin, each one has a unique 64-bit ID burned in at the factory to differentiate them. Usable with 3.0-5.0V systems.

The only downside is they use the Dallas 1-Wire protocol, which is somewhat complex, and requires a bunch of code to parse out the communication. There's a great Arduino library for 1-Wire, but some micro-controllers do not have support for 1-Wire so be sure to check!