// Libraries
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Adafruit_HDC1000.h"
#include <Wire.h>

Adafruit_HDC1000 hdc = Adafruit_HDC1000();
ESP8266WebServer server ( 80 );

// Set SDA and SDL ports for the HDC1000
const int hdc_sda = 14;
const int hdc_scl = 2;

// Set pin for the LDR
const int ldr = 9;

// Set pins for the Common Cathod RGB LED
const int ledRed = 12;
const int ledGreen = 13;
const int ledBlue = 15;

// Set which LEDs are going to be used.
const int ledWiFi = 16;

// Set WiFi constants
const char *ssid = "@400SoAve#";
const char *password = "589ShU!$305";
//const char *ssid = "theNile";
//const char *password = "stereo!3";
const char *dnsName = "esp8266-lee";

float currentTemp = 0.000;
float currentHumidity = 0.000;

// Functions
void connectWiFi();
char getWiFiAddress(void);
void handleRoot();
void handleNotFound();
void handleTemperature();
void handleHumidity();
int getTempCelsius(void);
int getTempFahrenheit(void);
int getTempKelvin(void);
int getHumidityRH(void);

// Create an ESP8266 WiFiClient class.
WiFiClient client;

/*************************** Sketch Code ************************************/
void setup ( void ) {
	pinMode ( ledWiFi, OUTPUT );
//  digitalWrite ( ledWiFi, 1 );
  Serial.begin ( 115200 );
  
  // Connect to Wifi
  connectWiFi();
  
  Serial.println("Setting up HDC100x...");
  Wire.begin(hdc_sda, hdc_scl);
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  
	server.on ( "/", handleRoot );
  server.on ( "/temperature", handleTemperature );
  server.on ( "/temperature/celsius", handleTemperatureC );
  server.on ( "/temperature/fahrenheit", handleTemperatureF );
  server.on ( "/temperature/kelvin", handleTemperatureK );
  server.on ( "/humidity", handleHumidity );
	server.on ( "/inline", []() {
		server.send ( 200, "text/plain", "this works as well" );
	} );
	server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println ( "HTTP server started" );
 
//  digitalWrite ( ledWiFi, 0 );
}

void loop ( void ) {
//  digitalWrite ( ledWiFi, 0 );
  server.handleClient();
  
  getWiFiAddress();
  
  float currentTemp = hdc.readTemperature();
  float currentHumidity = hdc.readHumidity();
  
  Serial.print("Temp: "); 
  Serial.print(currentTemp);
  Serial.print("C / ");
  Serial.print(currentTemp * 9/5 + 32);
  Serial.print("F"); 
  Serial.print("\tHum: "); 
  Serial.println(currentHumidity);

//  digitalWrite ( ledWiFi, 1 );
//  delay(180000); // 3 minutes
//  delay(30000); // 30 seconds
  delay(500); // .5 seconds
}

