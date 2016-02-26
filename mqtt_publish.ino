// Libraries
#include "Arduino.h"

void mqttPublish() {
  // Publish data
  if (! temperature_c.publish(currentTemp))
    Serial.println(F("Failed to publish temperature"));
  else
    Serial.println(F("C Temperature published!"));
    
  if (! temperature_f.publish(currentTemp * 9/5 + 32))
    Serial.println(F("Failed to publish temperature"));
  else
    Serial.println(F("F Temperature published!"));
  
  if (! humidity.publish(currentHumidity))
    Serial.println(F("Failed to publish humidity"));
  else
    Serial.println(F("Humidity published!"));

  delay(5000);
}
