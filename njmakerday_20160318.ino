// Libraries
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Adafruit_HDC1000.h"
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
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
//const char *ssid = "@400SoAve#";
//const char *password = "589ShU!$305";
const char *ssid = "theNile";
const char *password = "stereo!3";
const char *dnsName = "esp8266-lee.local";

float temperature_data = 0.000;
float humidity_data = 0.000;

// Functions
void connectWiFi();
void mqttConnect();
void mqttPublish();
void handleRoot();
void handleNotFound();
void handleTemperature();
void handleHumidity();

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "ProfeC"
#define AIO_KEY         "d85b8f1095d5f17816b3178be9e1ed7ea4e199df"
#define FEED_PATH_TEMPC AIO_USERNAME "/feeds/temperature-c";
#define FEED_PATH_TEMPF AIO_USERNAME "/feeds/temperature-f";
#define FEED_PATH_HUMIDITY AIO_USERNAME "/feeds/humidity";

// Store the MQTT server, client ID, username, and password in flash memory.
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;

// Set a unique MQTT client ID using the AIO key + the date and time the sketch
// was compiled (so this should be unique across multiple devices for a user,
// alternatively you can manually set this to a GUID or other random value).
const char MQTT_CLIENTID[] PROGMEM  = AIO_KEY __DATE__ __TIME__;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);

/****************************** Feeds ***************************************/
// Setup feeds for temperature & humidity
const char TEMPERATURE_C_FEED[] PROGMEM = FEED_PATH_TEMPC;
Adafruit_MQTT_Publish temperature_c = Adafruit_MQTT_Publish(&mqtt, TEMPERATURE_C_FEED);

const char TEMPERATURE_F_FEED[] PROGMEM = FEED_PATH_TEMPF;
Adafruit_MQTT_Publish temperature_f = Adafruit_MQTT_Publish(&mqtt, TEMPERATURE_F_FEED);

const char HUMIDITY_FEED[] PROGMEM = FEED_PATH_HUMIDITY;
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, HUMIDITY_FEED);

/*************************** Sketch Code ************************************/
void setup ( void ) {
	pinMode ( ledWiFi, OUTPUT );
//  digitalWrite ( ledWiFi, 1 );
  Serial.begin ( 115200 );
  
  // Connect to Wifi
  void connectWiFi();

  // connect to adafruit io
  mqttConnect();

 if ( MDNS.begin ( dnsName ) ) {
    Serial.println ( "MDNS responder started" );
  }
  

  Serial.println("Setting up HDC100x...");
  Wire.begin(hdc_sda, hdc_scl);
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  
	server.on ( "/", handleRoot );
  server.on ( "/temperature", handleTemperature );
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
  digitalWrite ( ledWiFi, 0 );
  server.handleClient();
  temperature_data = hdc.readTemperature();
  humidity_data = hdc.readHumidity();
  
  Serial.print("Temp: "); 
  Serial.print(temperature_data);
  Serial.print("C / ");
  Serial.print(temperature_data * 9/5 + 32);
  Serial.print("F"); 
  Serial.print("\tHum: "); 
  Serial.println(humidity_data);

  // Publish data
//  mqttPublish();

//  delay(180000); // 3 minutes
  digitalWrite ( ledWiFi, 1 );
//  delay(30000); // 30 seconds
}

