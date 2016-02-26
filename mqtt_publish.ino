// Libraries
#include "Arduino.h"

void mqttPublish() {
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

  delay(5000);
}
