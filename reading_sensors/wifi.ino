// Libraries
#include "Arduino.h"

void connectWiFi() {
  wifiMulti.addAP(ssid1, password1);        //if you have less SSID, delete the others
  wifiMulti.addAP(ssid2, password2);
//  wifiMulti.addAP(ssid3, password3);

  Serial.print("Connecting WiFi...");
  
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
  Serial.print("Connecting...\n");
  }

  digitalWrite ( ledWiFi, 1 );
  Serial.println ( "" );
  Serial.print ( "WiFi Connected" );
  getWiFiAddress();
}

char getWiFiAddress(void) {
  // Print the IP address out to the serial connection
  Serial.print ( "\n\nIP address: " );
  Serial.println ( WiFi.localIP() );

  return WiFi.localIP();
}
