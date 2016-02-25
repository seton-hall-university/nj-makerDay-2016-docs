// Libraries
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

// Set SDA and SDL ports for teh HDC1000
const int hdc_sda = 14;
const int hdc_scl = 2;

// Set WiFi constants
//const char *ssid = "@400SoAve#";
//const char *password = "589ShU!$305";
const char *ssid = "theNile";
const char *password = "stereo!3";
const char *dnsName = "esp8266-lee";

// Set which LEDs are going to be used.
const int ledWiFi = 16;

float temperature_data = 0.000;
float humidity_data = 0.000;

// Functions
void connect();
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

  // connect to adafruit io
  connect();

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
  if (! temperature_c.publish(temperature_data))
    Serial.println(F("Failed to publish temperature"));
  else
    Serial.println(F("C Temperature published!"));
    
  if (! temperature_f.publish(temperature_data * 9/5 + 32))
    Serial.println(F("Failed to publish temperature"));
  else
    Serial.println(F("F Temperature published!"));

  if (! humidity.publish(humidity_data))
    Serial.println(F("Failed to publish humidity"));
  else
    Serial.println(F("Humidity published!"));
  
//  delay(180000); // 3 minutes
  delay(30000); // 30 seconds
}

// connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}

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

/* Credits (that I can remember...)
 * Home Automation in the Cloud with the ESP8266 & Adafruit IO => https://learn.adafruit.com/home-automation-in-the-cloud-with-the-esp8266-and-adafruit-io/programming-the-modules
 *  Github => https://github.com/openhomeautomation/adafruit-io-esp8266/blob/master/esp8266_sensor_module/esp8266_sensor_module.ino
 * Many, many Google searches.

 */
