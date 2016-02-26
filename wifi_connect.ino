// Libraries
#include "Arduino.h"

void connectWiFi() {
  WiFi.begin ( ssid, password );
  Serial.println ( "" );
  
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite ( ledWiFi, 0 );
    delay ( 1000 );
     Serial.print ( "Connecting...\n" );

    Serial.print("Attempting to connect to SSID: ");
    Serial.println ( ssid );

    Serial.print("Current WiFi Status: ");
    Serial.println ( WiFi.status() );
  }

  digitalWrite ( ledWiFi, 1 );
  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  getWiFiAddress();
  
  if ( MDNS.begin ( dnsName ) ) {
    Serial.println ( "MDNS responder started" );
  }
}

char getWiFiAddress(void) {
  // Print the IP address out to the serial connection
  Serial.print ( "\n\nIP address: " );
  Serial.println ( WiFi.localIP() );

  return WiFi.localIP();
}

