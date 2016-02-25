#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include "Adafruit_HDC1000.h"
#include <Wire.h>

Adafruit_HDC1000 hdc = Adafruit_HDC1000();
ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server ( 80 );

// Set SDA and SDL ports
const int hdc_sda = 14;
const int hdc_scl = 2;

// Set WiFi constants
const char *ssid = "@400SoAve#";
const char *password = "589ShU!$305";
//const char ssid[] = "theNile";
//const char password[] = "stereo!3";

const char *dnsName = "esp8266-lee";
// Set which LEDs are going to be used.
const int ledWiFi = 16;

void handleRoot() {
	digitalWrite ( ledWiFi, 1 );
	char temp[600];
	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;

	snprintf ( temp, 600,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
  </body>\
</html>",

		hr, min % 60, sec % 60
	);
	server.send ( 200, "text/html", temp );
	digitalWrite ( ledWiFi, 0 );
}

void handleNotFound() {
	digitalWrite ( ledWiFi, 1 );
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ) {
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}

	server.send ( 404, "text/plain", message );
	digitalWrite ( ledWiFi, 0 );
}

void handleTemperature() {
  String out = "";
  out += "[{\"currentTempC\":";
  out += hdc.readTemperature();
  out += "},{\"currentTempF\":";
  out += hdc.readTemperature() * 9/5 + 32;
  out += "}]";
  server.send ( 200, "application/json", out );
}

void handleHumidity() {
  String out = "";
  out += "[{\"currentHumidity\":";
  out += hdc.readHumidity();
  out += "}]";
  server.send ( 200, "application/json", out );
}

void setup ( void ) {
	pinMode ( ledWiFi, OUTPUT );
	Serial.begin ( 115200 );
  
	WiFi.begin ( ssid, password );
	Serial.println ( "" );

	// Wait for connection
	while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite ( ledWiFi, 0 );
		delay ( 1000 );
		// Serial.print ( "Connecting...\n" );

    Serial.print("Attempting to connect to SSID: ");
    Serial.println ( ssid );

    Serial.print("Current WiFi Status: ");
    Serial.println ( WiFi.status() );
	}

  digitalWrite ( ledWiFi, 1 );
  Serial.println ( "" );
	Serial.print ( "Connected to " );
	Serial.println ( ssid );
	Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );

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
}

void loop ( void ) {
  server.handleClient();
  
  Serial.print("Temp: "); 
  Serial.print(hdc.readTemperature());
  Serial.print("C / ");
  Serial.print(hdc.readTemperature() * 9/5 + 32);
  Serial.print("F"); 
  Serial.print("\tHum: "); 
  Serial.println(hdc.readHumidity());
  
  delay(5000);
}
