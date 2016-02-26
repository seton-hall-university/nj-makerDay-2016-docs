// Libraries
#include "Arduino.h"

// connect to adafruit io via MQTT
void mqttConnect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("MQTT: Wrong protocol")); break;
      case 2: Serial.println(F("MQTT: ID rejected")); break;
      case 3: Serial.println(F("MQTT: Server unavail")); break;
      case 4: Serial.println(F("MQTT: Bad user/pass")); break;
      case 5: Serial.println(F("MQTT: Not authed")); break;
      case 6: Serial.println(F("MQTT: Failed to subscribe")); break;
      default: Serial.println(F("MQTT: Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}
