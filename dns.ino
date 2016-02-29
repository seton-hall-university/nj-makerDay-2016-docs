/*
 * "This is an almost line for line copy of the example that is included with the ESP8266 Arduino library."
 * 
 * ESP8266 mDNS responder sample
 * 
 * This is an example of an HTTP server that is accessible via http://esp8266.local URL thanks to mDNS responder.
 * 
 * Instructions:
 * - Update WiFi SSID and password as necessary.
 * - Flash the sketch to the ESP8266 board  
 * - Install host software:    
 * - For Linux, install Avahi (http://avahi.org/).    
 * - For Windows, install Bonjour (http://www.apple.com/support/bonjour/).    
 * - For Mac OSX and iOS support is built in through Bonjour already.  
 * - Point your browser to http://esp8266.local, you should see a response.
 * 
 */
 
// Libraries
#include "Arduino.h"


void setupDNS(void){
  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is setup in the main .ino file.
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin(dnsName)) {
    Serial.println("Error setting up MDNS responder!");
    while(1) { 
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  
  // Start TCP (HTTP) server
//  server.begin();
//  Serial.println("TCP server started");
  
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
}
